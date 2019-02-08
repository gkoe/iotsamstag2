#include "KY_037.h"
#include <Arduino.h>
#include <math.h>
#include <ThingTime.h>

KY_037::KY_037( uint8_t dpin, uint8_t apin, uint8_t interval, const char* thingName,  const char* name, const char* unit, float threshold)
	: StateMachine(interval, thingName, name, unit, threshold)
{
	gpio_pad_select_gpio(dpin);
	gpio_pad_select_gpio(apin);
	pinMode (dpin, INPUT);
 	pinMode (apin, INPUT);
	_dpin = dpin;
	_apin = apin;
	_threshold = 0;
	_divid = 0;
	_average = 0;
	calibrate();
}

float KY_037::getDB() {
	return _db;
}

float KY_037::getMeasure() {
	long time = ThingTime.getDateTime();
	if(time > _time + 900) {
		calibrate();
		_time = time;
	}
  	int digital, analog;
	float result;
	analog = analogRead (_apin); 
  	digital = digitalRead (_dpin);	
	if(analog - _average >= _threshold){
		result = 20 * log10((analog / _divid) + pow(analog - _threshold * 0.75 - _average , 3));
		Serial.printf("DB is: %f und analog: %i\n", result, analog);
		return result;
	}
	return -1;
}

void KY_037::calibrate() {
	int analog;
	for(int i = 0; i < 100; i++)
	{
		_average += analogRead (_apin);
		delay(10);
	}
	_average = _average / 99;
	_divid = _average / 50;
	Serial.println(_divid);
	Serial.println(_average);
	if(_average > 500) {
		_threshold = _average / 100 * 1.5;
	} else {
		_threshold = 5;
	}
	Serial.println(_threshold);
}

