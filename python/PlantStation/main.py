import json

from Communication.WiFiConnection.WiFiConnection import WiFiConnection
from Entities.DDD.MeasurementOfStation import MeasurementOfStation

# Via WiFi Schnittstelle eine Verbindung zum Mikrocontroller herstellen
# import requests

# IP-Adresse des D1 mini (Diese wird beim Start im Serial Monitor angezeigt)
URL = "http://192.168.178.74/data"

count_measurements_max = 1000
count_measurements = 0

wifi_connection = WiFiConnection(URL)

while count_measurements<count_measurements_max:
    count_measurements += 1
    print("Anzahl Messwerte: ", count_measurements)


    received_json_string = wifi_connection.fetch_data()
    measurements_dict = json.loads(received_json_string)
    measurement = MeasurementOfStation(measurements_dict)
    print()
print()
# # Via serieller Schnittstelle eine Verbindung zum Mikrocontroller herstellen
# ser = serial.Serial('COM6', 9600)
# time.sleep(2)  # Warten für die serielle Verbindung
#
# # Leere Liste erstellen
# data_list = []
#
# i = 0
#
# # Eine Textdatei zum Speichern öffnen
#
# with open('water_level_data.txt', 'w', encoding='utf-8') as f:
#     try:
#         while True:
#             line = ser.readline()  # Lese eine Zeile vom Mikrocontroller
#             try:
#                 decoded_line = line.decode('utf-8').strip()  # Versuche, die Zeile zu dekodieren
#             except UnicodeDecodeError:
#                 decoded_line = line.decode('latin-1').strip()  # Verwende latin-1 als Fallback
#
#             if len(data_list)%10 == 0:
#                 i+=1
#             print(i, decoded_line)  # Gebe die Zeile auf der Konsole aus
#
#             # Füge den dekodierten Wert zur Liste hinzu
#             data_list.append(decoded_line)
#
#             # Überprüfen, ob die Liste 1000 Einträge hat
#             if len(data_list) >= 10010:
#                 break  # Beende die Schleife, wenn 1000 Einträge erreicht sind
#
#     except KeyboardInterrupt:
#         print("Aufzeichnung beendet.")
#     finally:
#         # Schreibe alle gesammelten Werte in die Datei
#         for item in data_list:
#             f.write(item + '\n')  # Schreibe jeden Wert in eine neue Zeile
#
#         # Stelle sicher, dass der COM-Port geschlossen wird, falls er noch geöffnet ist
#         if ser.is_open:
#             ser.close()