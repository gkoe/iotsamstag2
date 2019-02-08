#include "Beeper.h"

Beeper::Beeper(int pin, const char* thingName, const char* name )
	:Actor(thingName, name)
{
	// ledcSetup(0, 2000, 8);
	// ledcAttachPin(pin, 0);
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void Beeper::setActorTo(float value)
{
	if (value > 0.5)
	{
		Serial.println(F("*PS: set pin high!"));
		digitalWrite(_pin, HIGH);
		// ledcWriteTone(_pin, 1000);
	}
	else
	{
		Serial.println(F("*PS: set pin low!"));
		digitalWrite(_pin, LOW);
		// ledcWriteTone(_pin, 0);
	}
}

float Beeper::readStateFromActor()
{
	if (digitalRead(_pin) == HIGH)
	{
		return 1;
	}
	else{
		return 0;
	}
}
