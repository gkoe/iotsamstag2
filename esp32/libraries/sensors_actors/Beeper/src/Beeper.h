
#include <Arduino.h>
#include <Actor.h>

class Beeper : public Actor 
{
	public:
		Beeper(int pin, const char* thingName, const char* name);
	
		virtual void setActorTo(float value);
		virtual float readStateFromActor();

	private:
		int _pin;
};
