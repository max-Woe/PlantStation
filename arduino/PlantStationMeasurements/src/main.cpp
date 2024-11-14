#include <SPI.h>
// #include <Arduino.h>
// #include <DHT.h>
// #include <string>
// #include <ArduinoMqttClient.h>
// #include <ESP8266WebServer.h>

#include <Communication\WiFi\WiFiConnection.h>
#include <Communication\WiFi\secrets.h>
#include <Measurements\Measurements.h>
#include <Measurements\Sensors\Sensors.h>
#include <Uhr\Uhr.h>


WiFiConnection wifi_connection(SECRET_SSID, SECRET_PASS);
Measurements measurements;
TemperatureHumiditySensor tempHumSensor;
WaterLevelSensor waterLevelSensor;


void setup() {
    Serial.begin(9600);
    wifi_connection.connect();
}

void loop() {
    tempHumSensor.fetchData();
    waterLevelSensor.fetchData();

    measurements.setTemperature(tempHumSensor.getTemperature());
    measurements.setHumidity(tempHumSensor.getHumidity());
    measurements.setWaterLevel(waterLevelSensor.getWaterLevel());



    Serial.print("temperatur:");
    String measurements_string = measurements.getAllMeasurementsAsJson();
    Serial.println(measurements_string);
    wifi_connection.setDataToSend(measurements_string);
    wifi_connection.handleDataRequest();
    wifi_connection.handle_client();
    wifi_connection.sendData(measurements_string);

    delay(2000);
}