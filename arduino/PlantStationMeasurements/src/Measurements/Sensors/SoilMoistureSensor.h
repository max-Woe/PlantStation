// #ifndef SENSORS_H
// #define SENSORS_H

// #include <Arduino.h>
// #include <DHT.h>
// #include <ArduinoJson.h>
// #include <Uhr\Uhr.h>

// class TemperatureSensor
// {
//     public:
//         // TemperatureSensor(const int DHTPIN,const int DHTTYPE);
//         TemperatureSensor();
        
//         void fetch_data();
//         float get_temperature();
//         DateTime get_time_stamp();
//         String get_measurement_as_json();

//     private:
//         DHT dht;
//         DateTime _time_stamp;
//         Uhr _uhr;
//         float temperature;
//         JsonDocument measurement_as_json;
// };

// #endif