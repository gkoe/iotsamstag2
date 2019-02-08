#pragma once

#include <Actor.h>

#define RGB_RED 99 * 100 * 100
#define RGB_GREEN 99 * 100
#define RGB_BLUE 99
#define RGB_OFF 0

/*
	RgbLed ist ein Aktor, dem über einen Floatvalue die Helligkeit für Rot, Grün und
	Blau so übermittelt werden, dass die Einer/Zehnerstelle Blau in %, die Hunderter/Tausenderstelle Grün
	und die Zehntausender/Hunderttausenderstelle Rot in Prozent angibt.
	Die Helligkeit wird über PWM gesteuert
*/
class RgbLed : public Actor
{
public:
	RgbLed(const int pinR, const int pinG, const int pinB, 
			const char *thingName, const char *name);

	virtual void setActorTo(float value);
	virtual float readStateFromActor();

	// Mapping nicht wie Standard-Aktor ON/OFF ==> 1/0 sondern RGB-Wert
	virtual float mapPayloadToCommandValue(const char *payload);
	virtual void mapStateValueToPayload(char *payload, float state);

private:
	int _pinR;
	int _pinG;
	int _pinB;
	int _ledChannelR = 1;	// IO-Pin wird per PWM angesteuert
	int _ledChannelG = 2;
	int _ledChannelB = 3;
};
