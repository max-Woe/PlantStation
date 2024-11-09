#include <SPI.h>
#include <Arduino.h>
#include <DHT.h>
#include <string>
#include <ArduinoMqttClient.h>
#include <ESP8266WebServer.h>
// #include <RTClib.h>

#include <Communication\WiFi\WiFiConnection.h>
#include <Measurements\Measurements.h>
#include <Uhr\Uhr.h>

#define DHTPIN1 D4
#define DHTTYPE DHT22
#define SECRET_SSID "PowaNet"
#define SECRET_PASS "31388112691306647290"

Measurements measurements(DHTPIN1, DHTTYPE);

WiFiConnection wifi_connection(SECRET_SSID, SECRET_PASS);

// RTC_DS3231 rtc;

// char wochentage[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};


void setup() {
    Serial.begin(9600); // Serielle Kommunikation initialisieren
    wifi_connection.connect();
//     if (! rtc.begin()) {
//     Serial.println("Finde keine RTC");
//     while (true);
//   }

//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Zeit vom Compiler
}

void loop() {
    // Uhr uhr;

    // DateTime jetzt = rtc.now();
    // Serial.print(uhr.get_day(), DEC);
    // Serial.print('.');
    // Serial.print(uhr.get_month(), DEC);
    // Serial.print('.');
    // Serial.print(uhr.get_year(), DEC);
    // Serial.print(" ");
    // Serial.print(uhr.get_day_of_week_string());
    // Serial.print(" ");
    // Serial.print(uhr.get_hour(), DEC);
    // Serial.print(':');
    // Serial.print(uhr.get_minute(), DEC);
    // Serial.print(':');
    // Serial.print(uhr.get_second(), DEC);
    // Serial.println();
    // //Formatierung vom Datum und der Zeit
    // char buf1[] = "DD.MMM.YYYY-hh:mm:ss";
    // Serial.println(uhr.get_date().toString(buf1));
    // delay(3000);


    measurements.collect_data();
    String measurements_string = measurements.get_all_measurements_as_json();
    wifi_connection.setDataToSend(measurements_string);
    wifi_connection.handleDataRequest();
    wifi_connection.handle_client();
    wifi_connection.sendData(measurements_string);

    Serial.println("Einzelmessungen:");
    measurements.get_water_level();
    measurements.get_humidity_of_sensor();
    measurements.get_temperature_of_sensor();
    Serial.println("Gesammt:");
    measurements.get_all_measurements();
    delay(2000);
}