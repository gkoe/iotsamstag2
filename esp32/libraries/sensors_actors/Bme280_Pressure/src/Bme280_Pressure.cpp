#include "Bme280_Pressure.h"

Bme280_Pressure::Bme280_Pressure(Adafruit_BME280* bme, const char* thingName, const char* name,const char* unit, float threshold) 
		:Sensor( thingName, name, unit, threshold)
{
	_bme = bme;
}

void Bme280_Pressure::measure()
{
	float pressure = _bme->readPressure() / 100.0F;
	setMeasurement(pressure);
}
