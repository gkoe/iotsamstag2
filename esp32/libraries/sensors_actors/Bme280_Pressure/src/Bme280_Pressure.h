#pragma once

#include <Adafruit_BME280.h>
#include <Sensor.h>

class Bme280_Pressure : public Sensor
{
public:
	Bme280_Pressure(Adafruit_BME280* bme, const char* thingName, const char* name, const char* unit, float threshold);
	virtual void measure();
private:
	Adafruit_BME280* _bme;
};
