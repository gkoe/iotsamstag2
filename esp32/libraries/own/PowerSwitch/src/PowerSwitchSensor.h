#ifndef _POWERSWITCHSENSOR_h
#define _POWERSWITCHSENSOR_h

#include "arduino.h"
#include "Sensor.h"

/*
	Der PowerSwitchSensor ist der zum Actor PowerSwitch zugehörige Sensor.
	Damit wird der aktuelle Zustand des digitalen Schaltpins ausgelesen.
*/
class PowerSwitchSensor : public Sensor
{

public:
	PowerSwitchSensor(const char* nodeName, const char* name, const char* unit, float threashold, uint8_t pinNumber);
	virtual void measure();

private:
	int _pinNumber;

};
#endif
