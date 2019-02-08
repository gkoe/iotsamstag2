#include "Dht22_Temperature.h"

Dht22_Temperature::Dht22_Temperature(Dht22* dht, const char* thingName, 
			const char* name, const char* unit, float threshold) 
		:Sensor(thingName, name, unit, threshold)
{
	_dht = dht;
}

void Dht22_Temperature::measure()
{
	float temperature = _dht->getTemperature();
	setMeasurement(temperature);
}
