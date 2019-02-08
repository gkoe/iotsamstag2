#pragma once
#include <Arduino.h>
#include <Sensor.h>
#include <Ticker.h>

class StateMachine : public Sensor
{
  public:
    StateMachine(uint8_t interval, const char* thingname,  const char* name, const char* unit, float threshold);
		virtual void measure();
		virtual float getMeasure() = 0;

  private:
		uint16_t _intervalMs;
		float _threshold;
		float _lastMeasure;
		float _average;
		float _sum;
		float _lastSendValue;
		Ticker _ticker;
		long _lastSendTime;
		int _status;
		int _counter;
		StaticJsonBuffer<200> _jsonBuffer;
};
