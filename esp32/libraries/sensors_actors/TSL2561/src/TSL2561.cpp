#include <Arduino.h>
#include "TSL2561.h"
#include <Adafruit_TSL2561_U.h>
#include <Wire.h>

TSL2561::TSL2561(uint8_t SDA, uint8_t SCL, const int interval, const char* thingname, const char * name, const char* unit, float threshold)
:StateMachine(interval, thingname, name, unit, threshold)
{
  _SDA = SDA;
  _SCL = SCL;
  tw = new TwoWire(4);
  tw->begin(_SDA, _SCL);
	if(!_tsl.begin(tw))
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
	//_tsl.begin();
	sensor_t sensor;
  _tsl.getSensor(&sensor);
  _tsl.enableAutoRange(true);
  _tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

float TSL2561::getMeasure() {
	uint16_t broadband = 0;
	uint16_t infrared = 0;
	_tsl.getLuminosity (&broadband, &infrared);
	Serial.printf("Lux: %lu \n", (unsigned long)broadband);
	//Serial.println(infrared);
	return broadband;
}

float TSL2561::getLux(){
    return _lux;
}
