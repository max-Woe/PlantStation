/**
 * @file TemperatureHumiditySensor.cpp
 * @brief implementation of the TemperatureHumiditySensor class
 */
#include "TemperatureHumiditySensor.h"

/**
 * Constructor: 
 * - defines the used baudrate for the sensor
 * - starts the DHT22 sensor
 */
TemperatureHumiditySensor::TemperatureHumiditySensor()
: dht(32,DHT22)  //D4, DHT22)
{}

void TemperatureHumiditySensor::begin()
{
    dht.begin();
    delay(2000);
}

// float TemperatureHumiditySensor::getTemperature()
// {
//     dht.readTemperature();
// }

/**
 * @brief Captures the temperature and humitiy values and updates the timestamp.
 * @details
 * Updates the internal timestamp
 * Reads the current sensor values
 * Stores the values and the updated timestamp
*/
// void TemperatureHumiditySensor::fetchData()
// {
//     _clock.update_time();
//     _temperature = getTemperature();
//     _humidity = getHumidity();
//     _time_stamp = _clock.get_date();
// }

/**
 * @brief Retrieves the current temperature value
 * @details
 * Reads the sensor value and stores it
 * @return temperature value in [°C]
*/
float TemperatureHumiditySensor::getTemperature()
{
    float temperatur_value = dht.readTemperature();
    
    return isnan(temperatur_value) ? -9999 : temperatur_value;
}

/**
 * @brief Retrieves the current humidity value
 * @details
 * Reads the sensor value and stores it
 * @return humidity value in [%rel]
*/
float TemperatureHumiditySensor::getHumidity()
{
    float humidity_value = dht.readHumidity();
    
    // Serial.print("Tempertur: ");
    // Serial.println(temperatur_value);
    return isnan(humidity_value) ? -9999 : humidity_value;
}

// /**
//  * @brief Retrieves the current time stamp
//   * @return time stamp in YYYY-MM-DD hh:mm:ss format
// */
// DateTime TemperatureHumiditySensor::getTimeStamp()
// {
//     return _time_stamp;
// }

// /**
//  * @brief Retrieves a json string containing the current timestamp and temperature
//  * @details
//  * Collects temperature and time stamp and stores them in an json string
//  * @return json string including 
//  * - time stamp in YYYY-MM-DD hh:mm:ss and temperature [°C]
// */
// String TemperatureHumiditySensor::getTemperatureMeasurementAsJson()
// {
//     _measurement_as_json["time_stamp"] = _clock.to_string();
//     _measurement_as_json["temperature"] = _temperature;
    
//     String jsonString;
//     serializeJson(_measurement_as_json, jsonString);
    
//     return jsonString;
// }

// /**
//  * @brief Retrieves a json string containing the current timestamp and humidity
//  * @details
//  * Collects temperature and time stamp and stores them in an json string
//  * @return json string including 
//  * - time stamp in YYYY-MM-DD hh:mm:ss and humidity [%rel]
// */
// String TemperatureHumiditySensor::getHumidityMeasurementAsJson()
// {
//     _measurement_as_json["time_stamp"] = _clock.to_string();
//     _measurement_as_json["humidity"] = _humidity;
    
//     String jsonString;
//     serializeJson(_measurement_as_json, jsonString);
    
//     return jsonString;
// }

// /**
//  * @brief Retrieves a json string containing the current timestamp and temperature and humitiy values
//  * @details
//  * Collects all values and stores them in an json string
//  * @return json string including 
//  * - time stamp in YYYY-MM-DD hh:mm:ss, temperature [°C] and humidity [%rel]
// */
// String TemperatureHumiditySensor::getAllMeasurementsAsJson()
// {
//     _measurement_as_json["time_stamp"] = _clock.to_string();
//     _measurement_as_json["temperature"] = _temperature;
//     _measurement_as_json["humidity"] = _humidity;
    
//     String jsonString;
//     serializeJson(_measurement_as_json, jsonString);
    
//     return jsonString;
// }