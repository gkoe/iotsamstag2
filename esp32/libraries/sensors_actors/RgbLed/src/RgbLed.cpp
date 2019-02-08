#include <RgbLed.h>
#include <Thing.h>
#include <Logger.h>

RgbLed::RgbLed(const int pinR, const int pinG, const int pinB, const char* thingName, 
		const char* name) : Actor(thingName, name)
{
	int freq = 500;
	int resolution = 8;
	_pinR = pinR;
	_pinG = pinG;
	_pinB = pinB;
	pinMode(_pinR, OUTPUT);
	pinMode(_pinG, OUTPUT);
	pinMode(_pinB, OUTPUT);
	ledcSetup(_ledChannelR, freq, resolution);
	ledcSetup(_ledChannelG, freq, resolution);
	ledcSetup(_ledChannelB, freq, resolution);
	ledcAttachPin(_pinR, _ledChannelR);
	ledcAttachPin(_pinG, _ledChannelG);
	ledcAttachPin(_pinB, _ledChannelB);
	ledcWrite(_ledChannelR, 0);
	ledcWrite(_ledChannelG, 0);
	ledcWrite(_ledChannelB, 0);
	Logger.debug("RgbLed", "Constructor");
}

void RgbLed::setActorTo(float value)
{
	_stateValue = value;
	char message[50];
	snprintf(message, 49, "setActorTo: %.0f", value);
	Logger.debug("RgbLed", message);
	int r = int (value / 10000);
	value -= r*10000;
	r=(r*256)/100;
	int g = int (value / 100);
	value -= g * 100;
	g=(g*256)/100;
	int b = (int) (value*256/100);
	ledcWrite(_ledChannelR, r);
	ledcWrite(_ledChannelG, g);
	ledcWrite(_ledChannelB, b);
}

float RgbLed::readStateFromActor()
{
	return _stateValue;
}

void RgbLed::mapStateValueToPayload(char* payload, float value){
	char message[50];
	snprintf(message, 49, "mapStateValueToPayload state: %.0f", value);
	Logger.debug("RgbLed", message);
	sprintf(payload, "%f", value);
}

/**
 * Übersetzt den Text aus der Payload in den Wert (Float), mit dem der
 * Aktor gesetzt werden soll.
 * Bei RgbLed wird direkt der RGB-Wert als int in float konvertiert und weitergegeben
 */
float RgbLed::mapPayloadToCommandValue(const char *payload){
	char message[50];
	snprintf(message, 49, "mapPayloadToCommandValue payload: %s", payload);
	Logger.debug("RgbLed", message);
	return atoi(payload);
}

