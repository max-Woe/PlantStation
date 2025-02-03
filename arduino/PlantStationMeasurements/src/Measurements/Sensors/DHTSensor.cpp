#include "DHTSensor.h"

// Konstruktor der DHTSensor-Klasse
DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

// Initialisierung des Sensors
void DHTSensor::begin() {
  dht.begin();
  delay(2000); // Warten, damit sich der Sensor stabilisieren kann
}

// Sensorwerte auslesen und ausgeben
void DHTSensor::readAndPrintData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Temperatur in Celsius

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Fehler beim Auslesen des DHT22 Sensors");
  } else {
    Serial.print("Temperatur: ");
    Serial.print(temperature);
    Serial.print(" °C  Feuchtigkeit: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}