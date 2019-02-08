#include "Bme280_Temperature.h"

Bme280_Temperature::Bme280_Temperature(Adafruit_BME280* bme, const char* thingName, const char* name,const char* unit, float threshold) 
		:Sensor( thingName, name, unit, threshold)
{
	_bme = bme;
}

void Bme280_Temperature::measure()
{
	float temperature = _bme->readTemperature();
	setMeasurement(temperature);
}
