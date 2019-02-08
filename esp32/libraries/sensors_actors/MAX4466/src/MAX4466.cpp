#include "MAX4466.h"
#include <Arduino.h>
#include <math.h>
#include <ThingTime.h>

MAX4466::MAX4466(uint8_t apin, uint8_t interval, const char* thingName,  const char* name, const char* unit, float threshold)
	: StateMachine(interval, thingName, name, unit, threshold)
{
	gpio_pad_select_gpio(apin);
 	pinMode (apin, INPUT);
	_apin = apin;
	_threshold = 0;
	_divid = 0;
	_average = 0;
	calibrate();
}

float MAX4466::getDB() {
	return _db;
}

float MAX4466::getMeasure() {
  	int analog;
	float result;
	analog = analogRead (_apin); 
	if(analog - _average >= _threshold){
		result = 20 * log10((analog / _divid) + pow(analog - _threshold - _average , 1.5));
		Serial.printf("DB is: %f und analog: %i\n", result, analog);
		return result;
	}
	return -1;
}

void MAX4466::calibrate() {
	int analog;
	for(int i = 0; i < 100; i++)
	{
		_average += analogRead (_apin);
		delay(10);
	}
	_average = _average / 99;
	_divid = _average / 10;
	Serial.println(_divid);
	Serial.println(_average);
	if(_average > 500) {
		_threshold = _average / 100 * 4;
	} else {
		_threshold = 5;
	}
	Serial.println(_threshold);
}

