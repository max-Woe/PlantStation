#ifndef TEMPERATURESENSORS_H
#define TEMPERATURESENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <Uhr\Uhr.h>

class TemperatureHumiditySensor
{
    public:
        // TemperatureSensor(const int DHTPIN,const int DHTTYPE);
        TemperatureHumiditySensor();
        
        void fetchData();
        float getTemperature();
        float getHumidity();
        DateTime getTimeStamp();
        String getTemperatureMeasurementAsJson();
        String getHumidityMeasurementAsJson();
        String getAllMeasurementsAsJson();

    private:
        DHT dht;
        DateTime _time_stamp;
        Uhr _uhr;
        float _temperature;
        float _humidity;
        JsonDocument _measurement_as_json;
};

#endif