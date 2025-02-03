/**
 * @file WaterLevelSensor.cpp
 * @brief implementation of the WaterLevelSensor class
 */

#include "WaterLevelSensor.h"

/**
 * Constructor: defines the used baudrate for the sensor
 */

WaterLevelSensor::WaterLevelSensor()
{
    // Serial.begin(9600);
}

/**
 * @brief Captures the current water level and updates the timestamp.
 * @details
 * Updates the internal timestamp
 * Reads the analog sensor value
 * Converts the sensor value to a percentage (0-100%)
 * Stores the percentage value and the updated timestamp
*/


void WaterLevelSensor::fetchData()
{
    _clock.update_time();
    float water_level_value_analog = analogRead(34);    //A0);
    Serial.println(water_level_value_analog);
    _water_level_value_percentage = (water_level_value_analog/600 *100) > 100 ? 100 : water_level_value_analog/600 *100 <5 ? 0 : water_level_value_analog/600 *100 ;
    Serial.println(_water_level_value_percentage);
    _time_stamp = _clock.get_date();
}

/**
 * @brief Retrieves the current water level.
 * @return The water level as a percentage value (0-100%).
*/
DateTime WaterLevelSensor::getTimeStamp()
{
    return _time_stamp;
}

/**
 * @brief Retrieves the current measurement as Json string.
 * @return A JSON string containing the timestamp and water level (0-100%).
*/
String WaterLevelSensor::getMeasurementAsJson()
{
    _measurement_as_json["time_stamp"] = _clock.to_string();
    _measurement_as_json["water_level"] = _water_level_value_percentage;
    
    String jsonString;
    serializeJson(_measurement_as_json, jsonString);
    
    return jsonString;
}
/**
 * @brief Retrieves the current measurement as Json string.
 * @return A JSON string containing the timestamp and water level (0-100%).
*/
float WaterLevelSensor::getPercentageValue()
{
    return _water_level_value_percentage;
}