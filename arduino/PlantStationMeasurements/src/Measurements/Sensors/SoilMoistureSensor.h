#ifndef SOILMOISTURESENSORS_H
#define SOILMOISTURESENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <MeasurementClock\MeasurementClock.h>

class SoilMoistureSensor
{
    public:
        // TemperatureSensor(const int DHTPIN,const int DHTTYPE);
        SoilMoistureSensor();
        
        void fetch_data();
        float get_moisture();
        DateTime get_time_stamp();
        String get_measurement_as_json();

    private:
        DateTime _time_stamp;
        MeasurementClock _clock;
        float moisture_percentage;
        JsonDocument measurement_as_json;
};

#endif