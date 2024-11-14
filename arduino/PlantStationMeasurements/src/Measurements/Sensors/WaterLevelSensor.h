#ifndef WATERLEVELSENSORS_H
#define WATERLEVELSENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <Uhr\Uhr.h>

class WaterLevelSensor
{
    public:
        // TemperatureSensor(const int DHTPIN,const int DHTTYPE);
        WaterLevelSensor();
        
        void fetchData();
        float getWaterLevel();
        DateTime getTimeStamp();
        String getMeasurementAsJson();

    private:
        DateTime _time_stamp;
        Uhr _uhr;
        float _water_level;
        JsonDocument _measurement_as_json;
};

#endif