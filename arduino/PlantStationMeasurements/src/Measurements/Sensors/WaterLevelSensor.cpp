#include "WaterLevelSensor.h"

WaterLevelSensor::WaterLevelSensor()
{
    // dht(D4, DHT22);
    Serial.begin(9600);
    _time_stamp = _uhr.get_date();
}


void WaterLevelSensor::fetchData()
{
    _uhr.update_time();
    _water_level = getWaterLevel();
}

float WaterLevelSensor::getWaterLevel()
{
    float water_level_value_digital = analogRead(A0);
    float water_level_value_percentage = water_level_value_digital/1023 *100;
    // Serial.print("Wasserstand: ");
    // Serial.println(water_level_value_digital);
    // Serial.println(water_level_value_percentage);
    return water_level_value_percentage;
}

DateTime WaterLevelSensor::getTimeStamp()
{
    return _time_stamp;
}

String WaterLevelSensor::getMeasurementAsJson()
{
    _measurement_as_json["time_stamp"] = _uhr.to_string();
    _measurement_as_json["water_level"] = _water_level;
    
    String jsonString;
    serializeJson(_measurement_as_json, jsonString);
    
    return jsonString;
}