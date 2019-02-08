//#include <Logger.h>
#include <PowerSwitch.h>
#include <PowerSwitchSensor.h>
#include <Thing.h>

/*
	Der Schalter hat keine Einheit des Messwertes EIN/AUS und auch eine fixe Schwelle von 0.001,
	da sowieso nur die Werte 0 und 1 verwendet werden.
*/
PowerSwitch::PowerSwitch(const int pinNumber, const bool isInverse, const char* thingName, const char* name) : Actor(thingName, name)
{
	_pinNumber = pinNumber;
	_isInverse = isInverse;
	_commandValue = 0;
	pinMode(_pinNumber, OUTPUT);
	if(isInverse){
		digitalWrite(_pinNumber, 1);
	}
	else{
		digitalWrite(_pinNumber, 0);
	}
}

void PowerSwitch::setActorTo(float value)
{
	if(_isInverse){
		if (value > 0.5)
		{
			Serial.println(F("*PS: set pin low!"));
			digitalWrite(_pinNumber, 0); // inverse Logik
		}
		else
		{
			Serial.println(F("*PS: set pin high!"));
			digitalWrite(_pinNumber, 1);
		}
	}
	else{  // normale (nicht inverse Logik)
		if (value > 0.5)
		{
			Serial.println(F("*PS: set pin high!"));
			digitalWrite(_pinNumber, 1); // normale Logik
		}
		else
		{
			Serial.println(F("*PS: set pin low!"));
			digitalWrite(_pinNumber, 0);
		}

	}
}

float PowerSwitch::readStateFromActor()
{
	if(_isInverse){
		if (digitalRead(_pinNumber) == HIGH)
		{
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		if (digitalRead(_pinNumber) == HIGH)
		{
			return 1;
		}
		else{
			return 0;
		}
	}
}
