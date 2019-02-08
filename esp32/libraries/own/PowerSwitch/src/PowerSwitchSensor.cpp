#include <PowerSwitchSensor.h>

PowerSwitchSensor::PowerSwitchSensor(const char *nodeName, const char *name, const char *unit, float threashold, uint8_t pinNumber)
	: Sensor(nodeName, name, unit, threashold)
{
	Serial.print(F("*PS: Sensor initialized: "));
	Serial.println(name);
	_pinNumber = pinNumber;
}

void PowerSwitchSensor::measure()
{
	// inverse Logik
	if (digitalRead(_pinNumber) == 0)
	{
		// Serial.println(F("*PS: PowerSwitchSensor low ==> return 1"));
		setMeasurement(1);
	}
	else
	{
		setMeasurement(0);
		// Serial.println(F("*PS: PowerSwitchSensor high ==> return 0"));
	}
}
