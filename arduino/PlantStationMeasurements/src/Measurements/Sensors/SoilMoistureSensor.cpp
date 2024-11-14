// #include "TemperatureSensor.h"

// TemperatureSensor::TemperatureSensor()
// : dht(D4, DHT22)
// {
//     // dht(D4, DHT22);
//     Serial.begin(9600);
//     dht.begin();
//     _time_stamp = _uhr.get_date();
// }


// void TemperatureSensor::fetch_data()
// {
//     _uhr.update_time();
//     temperature = get_temperature();
// }

// float TemperatureSensor::get_temperature()
// {
//     float temperatur_value = dht.readTemperature();
    
//     // Serial.print("Tempertur: ");
//     // Serial.println(temperatur_value);
//     return temperatur_value;
// }

// DateTime TemperatureSensor::get_time_stamp()
// {
//     return _time_stamp;
// }

// String TemperatureSensor::get_measurement_as_json()
// {
//     measurement_as_json["time_stamp"] = _uhr.to_string();
    
//     String jsonString;
//     serializeJson(measurement_as_json, jsonString);
    
//     return jsonString;
// }