#ifndef MEASUREMNTS_H
#define MEASUREMNTS_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <Uhr\Uhr.h>

// #define DHTPIN D4
// #define DHTTYPE DHT22

class Measurements {
    public:
        Measurements(const int DHTPIN,const int DHTTYPE); // Konstruktor

        float get_temperature_of_sensor();
        float get_humidity_of_sensor();
        float get_water_level();
        void get_all_measurements();
        void collect_data();
        String get_all_measurements_as_json();
        DateTime get_time_stamp();

    private:
        DHT dht; // DHT-Objekt als Member-Variable
        DateTime _time_stamp;
        Uhr _uhr;
        float temperature;
        float humidity;
        float water_level;
        JsonDocument measurements_as_json;
};

#endif