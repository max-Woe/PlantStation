#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

/**
 * @class WiFiConnection
 * @brief A class made for establishing the connection between a WEMOS D1 mini and a WiFi network
 * 
 * This class provides functionality for establishing an WiFi connection and send sensor data this way
*/
class WiFiConnection
{
    public:
        /**
         * @brief standard constructor for WiFiConnection class
         */
        WiFiConnection(const char *SSID, const char *PASS);

        /**
        * @brief Attempts to establish a WiFi connection
        */
        void connect();
        
        /**
        * @brief disconnects the WiFi connection
        */
        void disconnect();
        
        /**
        * @brief Attempts to establish a WiFi connection
        */
        void handle_client();

        /**
         * @brief Sets up a handler for HTTP GET requests to the "/data" endpoint
         */
        void handleDataRequest();
        
        /**
         * @brief Sets the data string for the HTTP request
         */
        void setDataToSend(String newData);
        
        /**
         * @brief Sends the data for the HTTP request
         */
        void sendData(String data);
    
    private:
        char _SSID[50]; ///< networkname (enviromental variable)
        char _PASS[50]; ///< network password (enviromental variable)
         
        //TODO: 1000 sind nur für Test, also noch anpassen!!!
        char _data_to_send[1000];   ///< requestbody for HTTP request
        
        int connection_tries_failed; ///< status variable for connection tries
        const int connection_tries_max = 10; ///< max. count for connection tries
        WebServer server;    ///< webserver object for an ESP8266 microcontroller
};

#endif