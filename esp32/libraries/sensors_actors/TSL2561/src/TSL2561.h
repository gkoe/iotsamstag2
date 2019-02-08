#pragma once 

#include <Arduino.h>
#include <Adafruit_TSL2561_U.h>
#include <StateMachine.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class TSL2561 : public StateMachine
{
    public:
      TSL2561(uint8_t SDA, uint8_t SCL, const int interval, const char* thingname, const char * name, const char* unit, float threshold);
      float getLux();
			virtual float getMeasure();

    private:
      uint8_t _SDA;
      uint8_t _SCL;
      TwoWire *tw;
    	float _lux;
			Adafruit_TSL2561_Unified _tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
};
