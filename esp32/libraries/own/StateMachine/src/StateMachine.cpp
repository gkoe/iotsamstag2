#include "StateMachine.h"
#include <ThingTime.h>
#include <MqttClient.h>
#include <ThingConfig.h>
#include <string.h>
#include <Logger.h>
#include <Sensor.h>

#define WAITING 0
#define COUNTING 1

StateMachine::StateMachine(uint8_t interval, const char *thingName, const char *name, const char *unit, float threshold)
	:Sensor(thingName, name, unit, threshold)
{
	_intervalMs = interval * 1000;
	_threshold = threshold;
	_status = 0;
	_counter = 0;
	_sum = 0;
	_lastSendValue = 0;
}

void StateMachine::measure() {
	float actMeasure = getMeasure();
	if(actMeasure == -1) return;
	if(_lastSendTime + 903000 < millis()){
		setMeasurement(actMeasure);
		_lastSendTime = millis();
		_lastSendValue = actMeasure;
		return;
	}
	switch(_status){
		case WAITING:
			if(fabs(_lastSendValue - actMeasure) >= _threshold){
				setMeasurement(actMeasure);
				_lastSendValue = actMeasure;
				_status = COUNTING;
				_lastSendTime = millis();
				_lastMeasure = actMeasure;
				_average = actMeasure;
				_counter = 1;
				_sum = 0;
			}
			break;
		case COUNTING:
			_sum += actMeasure;
			_counter++;
			if(_intervalMs + _lastSendTime < millis()) { // Zeitintervall abgelaufen
				_average = _sum/_counter;
				if(fabs(_lastSendValue - _average) >= _threshold){ // Durschnitswert hat sich wesentlich verändert
					_counter = 1;
				} else { // Durschnitswert ist konstant
					_status = WAITING;
				}
				_sum = 0;
				_lastSendTime = millis();
				setMeasurement(_average);
				_lastSendValue = _average; 
			}
			break;
		default: 
			break;
	}
}
