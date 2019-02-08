#pragma once

#include <Arduino.h>
#include <Sensor.h>
#define  HARDWARESERIALNUMBER 2

/**
 * Der Mhz19b-Co2-Sensor wird am ESP32 über eine der drei hardwaremäßig verfügbaren
 * seriellen Schnittstellen angeschlossen. Die Pins, auf die die Schnittstelle 
 * gemappt werden sind konfigurierbar.
 * Bei jedem Reset wird der Sensor kalibriert. 
 */

class Mhz19b: public Sensor
{
  public:
  	Mhz19b(int rxPin, int txPin, const char* thingName, const char* name, const char* unit, float threshold);
    float getCo2();
    void calibrate();
  private:
  	virtual void measure();
    HardwareSerial* _hardwareSerialPtr;
    uint8_t _cmd_measure_co2[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
    uint8_t _calibrate[9] = {0xFF,0x01,0x87,0x00,0x00,0x00,0x00,0x00,0x78};
    uint8_t mhzCmdABCEnable[9] = {0xFF,0x01,0x79,0xA0,0x00,0x00,0x00,0x00,0xE6};
    uint8_t mhzCmdABCDisable[9] = {0xFF,0x01,0x79,0x00,0x00,0x00,0x00,0x00,0x86}; 
    unsigned long _lastMeasurementMilliSeconds=0;
    float _ppmCo2;
};

