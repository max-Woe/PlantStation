#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

class DHTSensor {
  public:
    DHTSensor(uint8_t pin, uint8_t type);
    void begin();
    void readAndPrintData();
  
  private:
    DHT dht;
};

#endif