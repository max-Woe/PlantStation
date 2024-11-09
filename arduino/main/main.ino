#include <DHT.h>

#define DHTPIN D4         // Datenpin des DHT11 mit D4 verbinden (entspricht GPIO2)
#define DHTTYPE DHT11     // DHT 11-Sensortyp definieren
#define BUFFERSIZE 1000

DHT dht1(DHTPIN, DHTTYPE);

float humidityBuffer[BUFFERSIZE];
float waterLevelBuffer[BUFFERSIZE];
float temperatureBuffer[BUFFERSIZE];
int registerIndex = 0;

void setup() {
  Serial.begin(9600);
  dht1.begin();
}

void loop() {
  int water_level_sensor = analogRead(A0);  // Wasserstandssensor lesen
  float humidity = dht1.readHumidity();             // Luftfeuchtigkeit auslesen
  float temperature = dht1.readTemperature();          // Temperatur in °C auslesen


  // Wasserstandssensorwert speichern
  //Serial.println("Wasserstandssensor: " + String(water_level_sensor));
  Serial.println(humidity);

  delay(1000);  // Warten für 2 Sekunden zwischen den Messungen
}