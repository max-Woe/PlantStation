#include "Sensors.h"

SoilMoistureSensor::SoilMoistureSensor()
{
    // Serial.begin(9600);
    pinMode(A0, INPUT);
    _time_stamp = _clock.get_date();
}


void SoilMoistureSensor::fetch_data()
{
    _clock.update_time();
    
    float moisture_value_analog = analogRead(33); //A0);
    moisture_percentage =  isnan(moisture_value_analog) ? -9999 : moisture_value_analog/1023*100;
}

float SoilMoistureSensor::get_moisture()
{
    return moisture_percentage;
}

DateTime SoilMoistureSensor::get_time_stamp()
{
    return _time_stamp;
}

String SoilMoistureSensor::get_measurement_as_json()
{
    measurement_as_json["time_stamp"] = _clock.to_string();
    
    String jsonString;
    serializeJson(measurement_as_json, jsonString);
    
    return jsonString;
}