#include "Dht22_Humidity.h"

Dht22_Humidity::Dht22_Humidity(Dht22* dht, const char* nodeName, const char* name,const char* unit, float threshold) 
		:Sensor( nodeName, name, unit, threshold)
{
	_dht = dht;
}

void Dht22_Humidity::measure()
{
	float humidity = _dht->getHumidity();
	// Serial.print("Humidity: ");
	// Serial.println(humidity);
	setMeasurement(humidity);
}
