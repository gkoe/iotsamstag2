#include "Bme280_Humidity.h"

Bme280_Humidity::Bme280_Humidity(Adafruit_BME280* bme, const char* thingName, const char* name,const char* unit, float threshold) 
		:Sensor( thingName, name, unit, threshold)
{
	_bme = bme;
}

void Bme280_Humidity::measure()
{
	float humidity = _bme->readHumidity();
	setMeasurement(humidity);
}
