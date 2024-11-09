#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WiFiConnection
{
    public:
        WiFiConnection(const char *SSID, const char *PASS);

        void connect();
        void disconnect();
        void handle_client();
        void handleDataRequest();
        void setDataToSend(String newData);
        void sendData(String data);
    
    private:
        char _SSID[50];
        char _PASS[50];
        char _data_to_send[1000]; //TODO: 1000 sind nur für Test, also noch anpassen!!!
        int connection_tries_failed; // Statusvariable für Verbindungsversuche
        const int connection_tries_max = 10; // Maximale Anzahl an Versuchen
        ESP8266WebServer server;
};

#endif