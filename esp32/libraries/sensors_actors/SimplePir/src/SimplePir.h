#include <Arduino.h>
#include <Sensor.h>


class SimplePir : public Sensor
{
  public:
    SimplePir( int pin, int interval, const char *thingName, const char *name, 
                const char *unit, float threshold);
  	virtual void measure();

  private:
    unsigned long  _lastMotionDetectedMs;
    int _pin;
    int _intervalMs; 
    bool _isMotion; 
};