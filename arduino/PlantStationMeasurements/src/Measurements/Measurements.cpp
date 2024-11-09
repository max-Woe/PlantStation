#include "Measurements.h"

// Konstruktor
Measurements::Measurements(const int DHTPIN,const int DHTTYPE) 
    : dht(DHTPIN, DHTTYPE) // Initialisierung des DHT-Objekts
{
    Serial.begin(9600); // Serial communication for debugging
    dht.begin(); // DHT-Sensor initialisieren
    Uhr _uhr;
    _time_stamp =_uhr.get_date();
}

float Measurements::get_temperature_of_sensor()
{
    
    float temperatur_value = dht.readTemperature();
    
    Serial.print("Tempertur: ");
    Serial.println(temperatur_value);
    return temperatur_value;
}

float Measurements::get_humidity_of_sensor()
{
    float humidity_value = dht.readHumidity();
    
    Serial.print("Luftfeuchtigkeit: ");
    Serial.println(humidity_value);
    return humidity_value;
}

float Measurements::get_water_level()
{
    float water_level_value_digital = analogRead(A0);
    float water_level_value_percentage = water_level_value_digital/1023 *100;
    Serial.print("Wasserstand: ");
    Serial.println(water_level_value_digital);
    Serial.println(water_level_value_percentage);
    return water_level_value_percentage;
}

void Measurements::get_all_measurements()
{
    get_temperature_of_sensor();
    get_humidity_of_sensor();
    get_water_level();
}

void Measurements::collect_data()
{
    _uhr.update_time();
    temperature = get_temperature_of_sensor();
    humidity = get_humidity_of_sensor();
    water_level = get_water_level();
}

String Measurements::get_all_measurements_as_json()
{
    measurements_as_json["time_stamp"] = _uhr.to_string();
    measurements_as_json["temperature"] = temperature;
    measurements_as_json["humidity"] = humidity;
    measurements_as_json["water_level"] = water_level;
    
    String jsonString;
    serializeJson(measurements_as_json, jsonString);
    
    return jsonString;
}

DateTime Measurements::get_time_stamp()
{
    return _time_stamp;
}
