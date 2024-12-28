import json

# from requests import postgres_session, session

from Communication.WiFiConnection.WiFiConnection import HttpConnection
from DataCollecting.DDD.MeasurementOfStation import MeasurementOfStation
from DataCollecting.ORM.Repos.MeasurementRepo import *
from DataCollecting.ORM.SQLConnection.PostgresConnection import *

# Via WiFi Schnittstelle eine Verbindung zum Mikrocontroller herstellen
# import requests

# IP-Adresse des D1 mini (Diese wird beim Start im Serial Monitor angezeigt)
# URL = "http://192.168.178.74/data"

count_measurements_max = 1000
count_measurements = 0

wifi_connection = HttpConnection()
#
postgres_connection = PostgresConnection()
#
# postgres_session = postgres_connection.get_session()

# measurement_table_class = MeasurementTableManager()
# whole_table = measurement_table_class.get_table()
print(os.getcwd())

#
# measurement_model = MeasurementModel(value=1, unit= "°C", sensor_id=3,recorded_at=datetime.now(),created_at=datetime.now())
#
# if postgres_session:
#     postgres_session.add(measurement_model)
#     postgres_session.commit()
#     print(postgres_session.query(MeasurementModel).all())


# Logging-Konfiguration für eine Log-Datei
try:
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(levelname)s - %(message)s',
        handlers=[
            logging.FileHandler(os.path.join(os.getcwd(), 'app.log'), mode='a'),
            logging.StreamHandler()  # Ausgabe auch auf der Konsole
            ]
    )
    logging.info("Logging wurde gestartet.")
    # logging.getLogger().handlers[0].flush()  # Erzwingt das sofortige Schreiben
except Exception as e:
    print(f"Fehler beim Setup des Loggings: {e}")

# default values - water level calibration
min_waterLevel = 1000
max_waterLevel = 0
mean_waterLevel = 0
mean_waterLevel_min = 0
mean_waterLevel_max = 0

retries = 50
retry_delay = 2  # Zeit in Sekunden zwischen den Versuchen

while count_measurements<count_measurements_max:
    print("Anzahl Messwerte: ", count_measurements+1)

    for attempt in range(retries):
        try:
            received_json_string = wifi_connection.fetch_data()
            print(received_json_string)
            measurements_dict = json.loads(received_json_string)
            measurement_of_station = MeasurementOfStation(measurements_dict)
            break
        except (json.JSONDecodeError, ValueError) as e:
            # Fehler beim Decodieren der JSON-Daten abfangen
            print(f"Fehler beim Decodieren der JSON-Daten: {e}")
            break  # Oder versuche es weiterhin, wenn nötig

        # except Exception as e:
        #     # Andere Fehler abfangen, z.B. bei der Verbindung
        #     print(f"Fehler beim Abrufen der Daten: {e}")
        #     print(f"Versuch {attempt + 1} fehlgeschlagen. Erneuter Versuch in {retry_delay} Sekunden...")

            # Warten und dann erneut versuchen
            time.sleep(retry_delay)
        else:
            print("Alle Versuche zum Abrufen der Daten sind fehlgeschlagen.")

    # if 'measurements_values_df' not in locals():
    #     measurements_values_df = measurement_of_station.measurements_df
    if 'waterLevel_df' not in locals():
        waterLevel_df = pd.DataFrame({'waterLevel': [measurement_of_station.water_level]})
    else:
        waterLevel_df = waterLevel_df._append({'waterLevel': measurement_of_station.water_level}, ignore_index=True)
    waterLevel_df = waterLevel_df.sort_values('waterLevel')
    if max_waterLevel < measurement_of_station.water_level:
        max_waterLevel =  measurement_of_station.water_level
    if min_waterLevel > measurement_of_station.water_level:
        min_waterLevel =  measurement_of_station.water_level
    mean_waterLevel_max = waterLevel_df['waterLevel'].tail(5).mean() if waterLevel_df.shape[0]>5 else waterLevel_df['waterLevel'].mean()
    mean_waterLevel_min = waterLevel_df['waterLevel'].head(5).mean() if waterLevel_df.shape[0]>5 else waterLevel_df['waterLevel'].mean()
    print("min:", waterLevel_df['waterLevel'].iloc[0]," max:",waterLevel_df['waterLevel'].iloc[-1],"mittel_min:",mean_waterLevel_min,"mittel_max:",mean_waterLevel_max)
    commits = []

    measurement_values_df = measurement_of_station.measurements_values_df
    if 'test_df' not in locals():
        test_df = measurement_values_df
    else:
        test_df = pd.concat([test_df, measurement_values_df], ignore_index=True)

    if waterLevel_df.shape[0]%100 == 0:
        print()

    # measurement_model = MeasurementModel(value=)
    #
    # commits.append(measurement_model)
    # measure_table_class.add_row(measurement_model)

    # for index, measurement in measurement_of_station.get_measurements_as_df().iterrows():
    #     measurement_model = MeasurementModel(
    #         value = measurement['value'],
    #         unit = measurement['unit'],
    #         sensor_id = index + 1,
    #         recorded_at = measurement['recorded_at'],
    #         created_at = measurement['created_at']
    #     )
    #     commits.append(measurement_model)
    #     measurement_table_class.add_row(measurement_model)
    # postgres_session.add_all(commits)
    # postgres_session.commit()
    # postgres_session.close()
    # postgres_connection.close()
    count_measurements += 1
    print()
print()