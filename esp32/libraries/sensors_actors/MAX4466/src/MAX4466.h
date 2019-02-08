#include <Arduino.h>
#include <StateMachine.h>
#include <Ticker.h>

class MAX4466 : public StateMachine
{
  public:
    MAX4466(uint8_t apin, uint8_t interval, const char* thingname,  const char* name, const char* unit, float threshold);
		float getDB();
		virtual float getMeasure();
		void calibrate();

  private:
		uint8_t _apin;
		float _average;
		float _divid;
		float _db;
		float _threshold;
};
