#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <Arduino.h>
// #include <DHT.h>
#include <ArduinoJson.h>
#include <Uhr\Uhr.h>
#include <Measurements\Sensors\Sensors.h>
#include <list>
// #include <string>

// #define DHTPIN D4
// #define DHTTYPE DHT22

class Measurements {
    public:
        Measurements(); // Konstruktor

        float getTemperature();
        float getHumidity();
        float getLaterLevel();
        void setTemperature(float temperature);
        void setHumidity(float humidity);
        void setWaterLevel(float water_level);
        void getAllMeasurements();
        String getAllMeasurementsAsJson();
        DateTime getTimeStampOfMeasurements();

    private:

        DateTime _time_stamp;
        Uhr _uhr;
        float _temperature;
        float _humidity;
        float _water_level;
        JsonDocument _measurements_as_json;
};

#endif