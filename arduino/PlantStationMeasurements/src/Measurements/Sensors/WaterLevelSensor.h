#ifndef WATERLEVELSENSORS_H
#define WATERLEVELSENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <MeasurementClock\MeasurementClock.h>

/**
 * @class WaterLevelSensor
 * @brief A class made for capturing the water level of an water container, 
 * used as plants water source.
 * 
 * This class provides functionality for collecting, storing, and retrieving
* water level data, including timestamps and JSON formatting.
*/
class WaterLevelSensor
{
    public:
        /**
         * @brief standard constructor for WaterLevelSensor class
         */
        WaterLevelSensor();
        
        /**
         * @brief captures sensor data as percentage value
         * 
         * this methode captures the analog sensor, converts it into a percentage value and stores it in _water_level_value_perentage.
         */
        void fetchData();

        /**
         * @brief returns the current water level value in percentage
         */
        float getWaterLevel();

        /**
         * @brief returns the time stamp of the measurement
         */
        DateTime getTimeStamp();

        
        /**
         * @brief returns the time stamp and matching measurement as Json string
         */
        String getMeasurementAsJson();

        /**
         * @brief returns the time stamp and matching measurement as Json string
         */
        float getPercentageValue();

    private:
        MeasurementClock _clock;   ///< object for time management
        
        DateTime _time_stamp;   //< time stamp of the current measurement
        float _water_level_value_percentage;   //< percentage value of the current measurement
        JsonDocument _measurement_as_json;   //< time stamp of the current measurement
};


#endif