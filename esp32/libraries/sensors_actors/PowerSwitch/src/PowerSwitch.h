#pragma once

#include <Actor.h>

/*
	PowerSwitch ist ein spezieller sehr einfacher Aktor als
	Ein/Ausschalter über einen digitalen Ausgang.
*/
class PowerSwitch : public Actor
{
 public:
	 PowerSwitch(const int pinNumber, const bool isInverse, const char* thingName, const char* name);
	/**
	 * Der konkrete Aktor ändert den Zustand entsprechend
	 * z.B. schaltet den Schalter ein/aus
	 */
	virtual void setActorTo(float value);
	
	/**
	 * Der konkrete Aktor liefert seinen aktuellen Zustand
	 */
	
	virtual float readStateFromActor();
private:
	int _pinNumber;
	bool _isInverse;
};

