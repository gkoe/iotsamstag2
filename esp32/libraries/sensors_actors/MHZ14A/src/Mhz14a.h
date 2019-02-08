#pragma once

#include <Arduino.h>
#include <Sensor.h>
#define  HARDWARESERIALNUMBER 2

/**
 * Der Mhz14a-Co2-Sensor wird am ESP32 über eine der drei hardwaremäßig verfügbaren
 * seriellen Schnittstellen angeschlossen. Die Pins, auf die die Schnittstelle 
 * gemappt werden sind konfigurierbar.
 * Bei jedem Reset wird der Sensor kalibriert. 
 */

class Mhz14a: public Sensor
{
  public:
  	Mhz14a(int rxPin, int txPin, const char* thingName, const char* name, const char* unit, float threshold);
    float getCo2();
    void calibrate();
  private:
  	virtual void measure();
    HardwareSerial* _hardwareSerialPtr;
    uint8_t _cmd_measure_co2[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
    uint8_t _calibrate[9] = {0xFF,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78};
    unsigned long _lastMeasurementMilliSeconds=0;
    float _ppmCo2;
};

