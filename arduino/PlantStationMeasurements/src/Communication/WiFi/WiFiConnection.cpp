#include "WiFiConnection.h"
#include <cstring> // für strncpy
// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>

// Server auf Port 80 erstellen
ESP8266WebServer server(80);

WiFiConnection::WiFiConnection(const char *SSID, const char *PASS) 
    // : connection_tries_failed(0) // Initialisierung der Versuche
{
    // SSID und PASS in die Klassenmitglieder kopieren
    strncpy(_SSID, SSID, sizeof(_SSID) - 1);
    _SSID[sizeof(_SSID) - 1] = '\0'; // Nullterminierung
    strncpy(_PASS, PASS, sizeof(_PASS) - 1);
    _PASS[sizeof(_PASS) - 1] = '\0'; // Nullterminierung

    // Initialisiere _data_to_send
    strncpy(_data_to_send, "Initial data to send", sizeof(_data_to_send) - 1);
    _data_to_send[sizeof(_data_to_send) - 1] = '\0'; // Nullterminierung
}

/**
 * @brief Attempts to establish a WiFi connection
 * @details
 * This method tries to connect to the WiFi network using the stored SSID and password.
 * It will make multiple attempts, with a delay of 5 seconds between each attempt.
 * If successful, it prints the assigned IP address and starts the server.
 * If unsuccessful after a maximum number of attempts, it reports the failure.
 */
void WiFiConnection::connect()
{  
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(_SSID);
    
    WiFi.begin(_SSID, _PASS);

    while (WiFi.status() != WL_CONNECTED) 
    {
        // failed, retry
        connection_tries_failed++;
        Serial.print(".");
        delay(5000);
        
        if (connection_tries_failed >= connection_tries_max) {
            Serial.println("Connection failed!");
            break; // Maximalversuche erreicht
        }
    }

    if (WiFi.status() == WL_CONNECTED) 
    {
        Serial.println("Connection established!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        
        server.begin();
    } 
    else 
    {
        Serial.print("Connection failed after ");
        Serial.print(connection_tries_max);
        Serial.println(" tries!");
    }
}

void WiFiConnection::disconnect()
{
    WiFi.disconnect();
    Serial.println("Connection closed!");
}

/**
 * @brief Handles incoming client requests
 */
void WiFiConnection::handle_client()
{
    server.handleClient();
}

/**
 * @brief Sets up a handler for HTTP GET requests to the "/data" endpoint
 * @details
 * This method configures the server to respond to GET requests on the "/data" path.
 * When a request is received, it sends the content of _data_to_send as a plain text response.
 */
void WiFiConnection::handleDataRequest() {
    server.on("/data", HTTP_GET, [this]() 
    {
        String data = _data_to_send; 
        server.send(200, "text/plain", data);
    });
}

/**
 * @brief Sets the data string for the HTTP request
 * @details
 * This method:
 * - receives the data string for the HTTP request
 * - checks the data string for the right length
 * - stores the data string
 */
void WiFiConnection::setDataToSend(String newData) 
{
    if (newData.length() >= sizeof(_data_to_send)) {
        Serial.println("Error: newData is too long to fit in _data_to_send.");
        return; 
    }

    strncpy(_data_to_send, newData.c_str(), sizeof(_data_to_send) - 1);
    _data_to_send[sizeof(_data_to_send) - 1] = '\0'; 
}

/**
 * @brief Sends the data for the HTTP request
 * @details
 * This method:
 * - collects the data
 * - configures the server
 * - processes the incoming client request
 * 
 * @param data The string data to be sent to clients.
 */
void WiFiConnection::sendData(String data)
{
    setDataToSend(_data_to_send);
    handleDataRequest();
    handle_client();
}