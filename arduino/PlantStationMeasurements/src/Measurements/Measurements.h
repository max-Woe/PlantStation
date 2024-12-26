/**
 * @file Measurements.h
 * @brief Defines the Measurements class for managing sensor data in a plant station.
 * 
 * This file contains the declaration of the Measurements class, which is responsible
 * for collecting, storing, and retrieving various sensor measurements for a plant station.
 */

#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <MeasurementClock\MeasurementClock.h>
#include <Measurements\Sensors\Sensors.h>
#include <list>

/**
 * @class Measurements
 * @brief A class made for collecting the measurements of all sensors of a plant station.
 * 
 * This class provides functionality for collecting, storing, and retrieving:
 * - temperature
 * - humidity
 * - water level
 * - soil moisture
 * data, including timestamps and JSON formatting.
*/

class Measurements {
    public:
        /**
         * @brief standard constructor for Measurements class
         */
        Measurements();

        /**
         * @brief returns the current timestamp in "YYYY.MM.DD hh:mm:ss" of the plant station
         */
        DateTime getTimestamp();
        
        /**
         * @brief returns the current temperature value in °C of the plant station
         */
        float getTemperature();
        
        /**
         * @brief returns the current humidity value in %rel of the plant station
         */
        float getHumidity();

        /**
         * @brief returns the current water level value in % of the plant station water source
         */
        
        float getWaterLevel();
        
        /**
         * @brief returns the current soil moisture value in % of the plant station
         */
        float getSoilMoisture();
        

        /**
         * @brief sets the current temperature value in °C of the plant station
         * @param temperature in °C
         */
        void setTemperature(float temperature);
        
        /**
         * @brief sets the current humidity value in %rel of the plant station
         * @param humidity in %rel
         */
        void setHumidity(float humidity);
        
        /**
         * @brief sets the current water level value in % of the plant station water source
         * @param waterlevel in %
         */
        void setWaterLevel(float waterLevel);
        
        /**
         * @brief sets the current soil moisture value in % of the plant station
         * @param soilMoisture in %
         */
        void setSoilMoisture(float soilMoisture);
                
        /**
         * @brief returns the current measurements of the plant station as Json string
         */
        String getAllMeasurementsAsJson();  
        
        /**
         * @brief returns the current timestamp in YYYY-MM-DD hh:mm:ss format of the plant station
         */
        DateTime getTimeStampOfMeasurements();

    private:
        MeasurementClock _clock;   //< object for time management

        DateTime _time_stamp;   ///< time stamp of the current measurement
        float _temperature; ///< temperature value of the plant station
        float _humidity;    ///< humidity value of the plant station
        float _waterLevel;  ///< water level value of the plant station
        float _soilMoisture;    ///< soil moisture value of the plant station
        JsonDocument _measurements_as_json; /// json string including all measurement values and time stamp of the plant station
};

#endif