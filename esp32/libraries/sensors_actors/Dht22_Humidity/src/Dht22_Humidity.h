#pragma once

#include <Dht22.h>
#include <Sensor.h>

class Dht22_Humidity : public Sensor
{
public:
	Dht22_Humidity(Dht22* dht, const char* nodeName, const char* name, const char* unit, float threshold);
	virtual void measure();
private:
	Dht22* _dht;
};
