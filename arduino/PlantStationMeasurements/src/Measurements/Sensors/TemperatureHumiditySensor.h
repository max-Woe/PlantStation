#ifndef TEMPERATUREHUMIDITYSENSORS_H
#define TEMPERATUREHUMIDITYSENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
// #include <MeasurementClock\MeasurementClock.h>

/**
 * @class TemperatureHumiditySensor
 * @brief A class made for capturing the temperature and humidty of DHT22 sensor
 * 
 * This class provides functionality for collecting, storing, and retrieving
* temperature and humidity data, including timestamps and JSON formatting.
*/

class TemperatureHumiditySensor
{
    public:
    
        /**
         * @brief standard constructor for WaterLevelSensor class
         */
        TemperatureHumiditySensor();
    
    
        /**
         * @brief starts the sensors: temperature[°C] and humidity[%rel]
         * 
         * this methode starts the sensors.
         */
        void begin();


        /**
         * @brief captures sensor data temperature[°C] and humidity[%rel]
         * 
         * this methode captures the sensor values and stores them in the matching variables.
         */
        void fetchData();

        /**
         * @brief returns the temperature value of the DHT22
         */
        float getTemperature();
        
        /**
         * @brief returns the humidity value of the DHT22
         */
        float getHumidity();
        
        // /**
        //  * @brief returns the timestamp when the current values were recorded
        //  */
        // DateTime getTimeStamp();
        
        // /**
        //  * @brief returns the temperature value and matching timestamp as Json string
        //  */
        // String getTemperatureMeasurementAsJson();
        
        // /**
        //  * @brief returns the humidity value and matching timestamp as Json string
        //  */
        // String getHumidityMeasurementAsJson();

        // /**
        //  * @brief returns the humidity value and matching timestamp as Json string
        //  */
        // String getAllMeasurementsAsJson();

        DHT dht;    ///< object of the DHT sensor class
    private:
        // MeasurementClock _clock;   ///< object for time management
        
        // DateTime _time_stamp;   ///< time stamp of the current measurements
        float _temperature; ///< temperature value of the current measurement
        float _humidity;    //< humidity value of the current measurement
        JsonDocument _measurement_as_json;  //<  json string of the current measurements and timestamp
};

#endif