#include "Measurements.h"
#include <list>
// #include <Arduino.h>

// Konstruktor 
// Übergabeparameter: Liste der Sensortypen (Temp, LF, FS)
// Measurements::Measurements(const int DHTPIN,const int DHTTYPE) 
//     : dht(DHTPIN, DHTTYPE) // Initialisierung des DHT-Objekts
// {
//     Serial.begin(9600); // Serial communication for debugging
//     dht.begin(); // DHT-Sensor initialisieren
//     Uhr _uhr;
//     _time_stamp =_uhr.get_date();
// }
Measurements::Measurements()
{
    _time_stamp = _uhr.get_date();
}

float Measurements::getTemperature()
{
        return _temperature;
}

void Measurements::setTemperature(float temperature)
{
    _temperature = temperature;
}

float Measurements::getHumidity()
{
        return _humidity;
}

void Measurements::setHumidity(float humidity)
{
    _humidity = humidity;
}

float Measurements::getLaterLevel()
{
        return _water_level;
    
}

void Measurements::setWaterLevel(float water_level)
{
    _water_level = water_level;
}

String Measurements::getAllMeasurementsAsJson()
{
    _measurements_as_json["time_stamp"] = _uhr.to_string();
    _measurements_as_json["temperature"] = _temperature;
    _measurements_as_json["humidity"] = _humidity;
    _measurements_as_json["water_level"] = _water_level;
    
    String jsonString;
    serializeJson(_measurements_as_json, jsonString);
    
    return jsonString;
}

DateTime Measurements::getTimeStampOfMeasurements()
{
    return _time_stamp;
}
