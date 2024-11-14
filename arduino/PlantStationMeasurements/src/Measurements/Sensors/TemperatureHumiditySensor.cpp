#include "TemperatureHumiditySensor.h"

TemperatureHumiditySensor::TemperatureHumiditySensor()
: dht(D4, DHT22)
{
    Serial.begin(9600);
    dht.begin();
    _time_stamp = _uhr.get_date();
}


void TemperatureHumiditySensor::fetchData()
{
    _uhr.update_time();
    _temperature = getTemperature();
    _humidity = getHumidity();
}

float TemperatureHumiditySensor::getTemperature()
{
    float temperatur_value = dht.readTemperature();
    
    // Serial.print("Tempertur: ");
    // Serial.println(temperatur_value);
    return temperatur_value;
}

float TemperatureHumiditySensor::getHumidity()
{
    float humidity_value = dht.readHumidity();
    
    // Serial.print("Tempertur: ");
    // Serial.println(temperatur_value);
    return humidity_value;
}

DateTime TemperatureHumiditySensor::getTimeStamp()
{
    return _time_stamp;
}

String TemperatureHumiditySensor::getTemperatureMeasurementAsJson()
{
    _measurement_as_json["time_stamp"] = _uhr.to_string();
    _measurement_as_json["temperature"] = _temperature;
    
    String jsonString;
    serializeJson(_measurement_as_json, jsonString);
    
    return jsonString;
}

String TemperatureHumiditySensor::getHumidityMeasurementAsJson()
{
    _measurement_as_json["time_stamp"] = _uhr.to_string();
    _measurement_as_json["humidity"] = _humidity;
    
    String jsonString;
    serializeJson(_measurement_as_json, jsonString);
    
    return jsonString;
}

String TemperatureHumiditySensor::getAllMeasurementsAsJson()
{
    _measurement_as_json["time_stamp"] = _uhr.to_string();
    _measurement_as_json["temperature"] = _temperature;
    _measurement_as_json["humidity"] = _humidity;
    
    String jsonString;
    serializeJson(_measurement_as_json, jsonString);
    
    return jsonString;
}