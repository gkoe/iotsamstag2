#include <Arduino.h>
#include "BLEDevice.h"
#include <Flower.h>

//static BLEAddress floraAddress();
Flower f("c4:7c:8d:67:2b:b6" , true);

void setup() {
  Serial.begin(115200);
  BLEDevice::init("");
  // put your setup code here, to run once:
}

void loop() {
  delay(10000);
  f.getSensorData();
  Serial.printf("Temperatur %f, Moisture: %i, Light: %i, Conductivity: %i, Battery: %i", f.getTemperature(), f.getMoisture(), f.getLight(), f.getConductivity(), f.getBattery());
  // put your main code here, to run repeatedly:
}