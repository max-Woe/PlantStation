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
    
    // // Webserver und Route einrichten
    // server.on("/data", HTTP_GET, [this]() { // [this] um auf die Instanz zuzugreifen
    //     String data = "Hello from D1 mini"; // Hier die Daten festlegen, die übertragen werden sollen
    //     this->server.send(200, "text/plain", data); // Zugriff auf server über this
    // });
}

void WiFiConnection::connect()
{  
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(_SSID);
    
    WiFi.begin(_SSID, _PASS);

    while (WiFi.status() != WL_CONNECTED) {
        // failed, retry
        connection_tries_failed++;
        Serial.print(".");
        delay(5000);
        
        if (connection_tries_failed >= connection_tries_max) {
            break; // Maximalversuche erreicht
        }
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connection established!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        
        
        
        server.begin();
    } else {
        Serial.print("Connection failed after ");
        Serial.print(connection_tries_max);
        Serial.println(" tries!");
    }

    // if (connection_tries_failed >= connection_tries_max) {
    //     Serial.print("Connection failed after ");
    //     Serial.print(connection_tries_max);
    //     Serial.println(" tries!");
    // } else {
    //     Serial.println("Connection established!");
    //     Serial.print("IP Address: ");
    //     Serial.println(WiFi.localIP());

    // }
}

void WiFiConnection::disconnect()
{
    WiFi.disconnect();
    Serial.println("Connection closed!");
}

void WiFiConnection::handle_client()
{
    server.handleClient();
}

void WiFiConnection::handleDataRequest() {
    server.on("/data", HTTP_GET, [this]() 
    {
        String data = _data_to_send; // Hier kannst du die Logik für den Text ändern
        server.send(200, "text/plain", data);
    });
}

void WiFiConnection::setDataToSend(String newData) {
    // Überprüfen, ob der neue Datenstring die Puffergröße überschreitet
    if (newData.length() >= sizeof(_data_to_send)) {
        Serial.println("Error: newData is too long to fit in _data_to_send.");
        return; // Oder handhaben Sie diesen Fehler entsprechend
    }

    // Kopieren des Strings in den Puffer
    strncpy(_data_to_send, newData.c_str(), sizeof(_data_to_send) - 1);
    _data_to_send[sizeof(_data_to_send) - 1] = '\0'; // Sicherstellen, dass der Puffer nullterminiert ist
}

void WiFiConnection::sendData(String data)
{
    setDataToSend(_data_to_send);
    handleDataRequest();
    handle_client();
}