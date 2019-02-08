#include <Arduino.h>
#include <Sensor.h>


class PIR : public Sensor
{
  public:
  PIR( int pin, int interval, const char *thingName, const char *name, const char *unit, float threshold);
  	virtual void measure();
    float getMotion();

  private:
   
    unsigned long _lastMeasurementMilliSeconds=0;
    int _acclimatizationMilliSeconds = 60000;
    int _delayTime=300;
    int _lastdetectionTime=0;
    float _motion;
    int _pin;
    int _interval; 
    float _motionCount;
    bool _state; 
     
};