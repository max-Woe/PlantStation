/**
 * @file Measurements.cpp
 * @brief implementation of the Measurements class
 */
#include "Measurements.h"
#include <list>

/**
 * @brief Constructor: sets the time stamp for the measurement
 */
Measurements::Measurements()
{
    _time_stamp = _clock.get_date();
}
DateTime Measurements::getTimestamp()
{
    _clock.update_time();
    
    return _clock.get_date_time();
}

/**
 * @brief Retrieves the temperature value of the measurement [°C]
 * @return temperature [°C]
 */
float Measurements::getTemperature()
{
        return _temperature;
}

/**
 * @brief sets the temperature value of the measurement [°C]
 * @param temperature [°C]
 */
void Measurements::setTemperature(float temperature)
{
    _temperature = temperature;
}

/**
 * @brief Retrieves the humidity value of the measurement [%rel]
 * @return humidity [%rel]
 */
float Measurements::getHumidity()
{
        return _humidity;
}

/**
 * @brief sets the humidity value of the measurement [%rel]
 * @param humidity [%rel]
 */
void Measurements::setHumidity(float humidity)
{
    _humidity = humidity;
}

/**
 * @brief Retrieves the water level value of the measurement [%]
 * @return water level value [%]
 */
float Measurements::getWaterLevel()
{
        return _waterLevel;
    
}

/**
 * @brief Set the water level value of the measurement [%]
 * @param waterLevel value [%]
 */
void Measurements::setWaterLevel(float waterLevel)
{
    _waterLevel = waterLevel;
}

/**
 * @brief Retrieves the soil moisture value of the measurement [%]
 * @return soil moisture [%]
 */
float Measurements::getSoilMoisture()
{
        return _soilMoisture;
    
}

/**
 * @brief Sets the soil moisture value of the measurement [%]
 * @param soilMoisture moisture [%]
 */
void Measurements::setSoilMoisture(float soilMoisture)
{
    _soilMoisture = soilMoisture;
}

/**
 * @brief Retrieves a Json string containing all measurements and the timestamp
 * @return jsonString with temperature, humidity, water level, and timestamp
 */
String Measurements::getAllMeasurementsAsJson()
{
    _clock.update_time();
    _measurements_as_json["time_stamp"] = _clock.to_string();
    _measurements_as_json["temperature"] = _temperature;
    _measurements_as_json["humidity"] = _humidity;
    _measurements_as_json["water_level"] = _waterLevel;
    _measurements_as_json["soil_moisture"] = _soilMoisture;
    
    String jsonString;
    serializeJson(_measurements_as_json, jsonString);
    
    return jsonString;
}

/**
 * @brief Retrieves the time stamp of the measurement 
 * @return time stamp in YYYY-MM-DD hh:mm:ss format 
 */
DateTime Measurements::getTimeStampOfMeasurements()
{
    return _time_stamp;
}
