#include <Arduino.h>
#include <StateMachine.h>
#include <Ticker.h>

class KY_037 : public StateMachine
{
  public:
    KY_037(uint8_t dpin, uint8_t apin, uint8_t interval, const char* thingname,  const char* name, const char* unit, float threshold);
		float getDB();
		virtual float getMeasure();
		void calibrate();
		void setMultiplier();

  private:
		uint8_t _dpin;
		uint8_t _apin;
		float _average;
		float _divid;
		float _db;
		float _threshold;
		long _time;
};
