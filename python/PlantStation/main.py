import json

# from requests import postgres_session, session

from Communication.WiFiConnection.WiFiConnection import HttpConnection
from DataCollecting.DDD.MeasurementOfStation import MeasurementOfStation
from DataCollecting.ORM.MeasurementTable import *
from DataCollecting.ORM.SQLConnection.PostgresConnection import *
from DataCollecting.ORM.AlembicModels.Measurement import MeasurementModel

# Via WiFi Schnittstelle eine Verbindung zum Mikrocontroller herstellen
# import requests

# IP-Adresse des D1 mini (Diese wird beim Start im Serial Monitor angezeigt)
# URL = "http://192.168.178.74/data"

count_measurements_max = 1000
count_measurements = 0

wifi_connection = HttpConnection()
#
# postgres_connection = PostgresConnection()
#
# postgres_session = postgres_connection.get_session()

measure_table_class = MeasurementTable()
whole_table = measure_table_class.get_table()
print()

#
# measurement_model = MeasurementModel(value=1, unit= "°C", sensor_id=3,recorded_at=datetime.now(),created_at=datetime.now())
#
# if postgres_session:
#     postgres_session.add(measurement_model)
#     postgres_session.commit()
#     print(postgres_session.query(MeasurementModel).all())



while count_measurements<count_measurements_max:
    count_measurements += 1
    print("Anzahl Messwerte: ", count_measurements)


    received_json_string = wifi_connection.fetch_data()
    measurements_dict = json.loads(received_json_string)
    measurement_of_station = MeasurementOfStation(measurements_dict)
    commits = []
    test = measurement_of_station.get_measurements_as_df()
    for _, measurement in measurement_of_station.get_measurements_as_df().iterrows():
        measurement_model = MeasurementModel(
            value = measurement['value'],
            unit = measurement['unit'],
            recorded_at = measurement['recorded_at'],
            created_at = measurement['created_at']
        )
        commits.append(measurement_model)
        measure_table_class.add_row(measurement_model)
    # postgres_session.add_all(commits)
    # postgres_session.commit()
    # postgres_session.close()
    # postgres_connection.close()
    print()
print()