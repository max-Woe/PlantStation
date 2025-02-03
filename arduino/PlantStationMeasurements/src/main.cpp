// #include <SPI.h>
// // #include <Arduino.h>
// // #include <DHT.h>
// // #include <string>
// // #include <ArduinoMqttClient.h>
// // #include <ESP8266WebServer.h>

// #include <Communication\WiFi\WiFiConnection.h>
// // // #include <Communication\WiFi\secrets.h>
// #include <Measurements\Measurements.h>
// // // #include <Measurements\Sensors\Sensors.h>
// #include <MeasurementClock\MeasurementClock.h>




// TemperatureHumiditySensor tempHumSensor;
// WiFiConnection wifi_connection(SECRET_SSID, SECRET_PASS);
// // Measurements measurements = Measurements();
// // WaterLevelSensor waterLevelSensor = WaterLevelSensor();
// // SoilMoistureSensor soilMoistureSensor;

// void setup() {
//     Serial.begin(9600);
//     tempHumSensor.dht.begin();
//     // wifi_connection.connect();
//     // Serial.println("setup done");
//     //// Uhr Test = Uhr();
// }

// void loop() {
//     Serial.println("loop läuft!");
//     // tempHumSensor.fetchData();
//     // // waterLevelSensor.fetchData();
//     // soilMoistureSensor.fetch_data();

//     // measurements.setTemperature(tempHumSensor.getTemperature());
//     // measurements.setHumidity(tempHumSensor.getHumidity());
//     // // measurements.setWaterLevel(waterLevelSensor.getPercentageValue());
//     // measurements.setSoilMoisture(soilMoistureSensor.get_moisture());

//     // String measurements_string = measurements.getAllMeasurementsAsJson();
//     // wifi_connection.setDataToSend(measurements_string);
//     // wifi_connection.handleDataRequest();
//     // wifi_connection.handle_client();
//     // DateTime timestamp = measurements.getTimestamp();
//     // String timestamp_str = String(timestamp.year()) + "-" +
//     //                     String(timestamp.month()) + "-" +
//     //                     String(timestamp.day()) + " " +
//     //                     String(timestamp.hour()) + ":" +
//     //                     String(timestamp.minute()) + ":" +
//     //                     String(timestamp.second());
//     // Serial.println("Zeit: " + timestamp_str);
//     // Serial.println(measurements_string);

//     //// Serial.print("Zeit: ");
//     //// Serial.println(measurements.getTimestamp().year());

//     //// Serial.print("testwert: ");
//     //// Serial.println(measurements.getTemperature());
//     //// Serial.println("End of main");
//     //// wifi_connection.sendData(measurements_string);


    
//     //// delay(2000);
//     // // Serial.print("SoilMoisture: ");
    
// }



#include <SPI.h>
#include <Arduino.h>


#include <Communication\WiFi\WiFiConnection.h>
#include <Measurements\Sensors\DHTSensor.h>
#include <Measurements\Sensors\TemperatureHumiditySensor.h>

// DHTSensor-Objekt erstellen
DHTSensor dhtSensor(32, DHT22); // DHT22 an Pin 4

TemperatureHumiditySensor dhtSensor2;
WiFiConnection wifi_connection(SECRET_SSID, SECRET_PASS);

void setup() {
  // Serielle Kommunikation starten
  Serial.begin(115200);
  
  wifi_connection.connect();
  // Sensor initialisieren
  dhtSensor.begin();
  dhtSensor2.begin();
}

void loop() {
    // Serial.println("loop");
  // Sensorwerte auslesen und auf der Konsole ausgeben
//   dhtSensor.readAndPrintData();
    // dhtSensor2.fetchData();
    Serial.println("------------------------------------------");
    Serial.print("Temperature: ");
    Serial.println(dhtSensor2.getTemperature());
    Serial.print("Humidity: ");
    Serial.println(dhtSensor2.getHumidity());
  // Eine Sekunde warten, bevor der nächste Messwert erfasst wird
  delay(1000);
}