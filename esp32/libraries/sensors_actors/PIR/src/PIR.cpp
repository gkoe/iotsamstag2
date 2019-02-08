#include "PIR.h"

PIR::PIR(int pin, int interval, const char *thingName, const char *name, const char *unit, float threshold) : Sensor(thingName, name, unit, threshold)
{
  _pin = pin;
  pinMode(_pin, INPUT);
  _state = 0;
  _interval = interval * 1000;
}

float PIR::getMotion()
{
  bool isDetected = digitalRead(_pin);
  if (isDetected)
  {
    return 1.0;
  }
  else
  {
    return 0.0;
  }
  return 0.0;
}

void PIR::measure()
{
  if (millis() > _acclimatizationMilliSeconds && (_delayTime + _lastdetectionTime < millis()))
  {
    float motion = getMotion();
    switch (_state)
    {
    case 0:
    if(motion != 0){
      setMeasurement(motion);
      _state = 1;
      _lastMeasurementMilliSeconds = millis();
      _motionCount = 1;
      }
      break;
    case 1:
      if (_interval + _lastMeasurementMilliSeconds < millis())
      {
          Serial.println(_motionCount);
        if (_motionCount == 1.0)
        {
          _state = 0;
          setMeasurement(0.0);
          break;
        }
        else
        {
          setMeasurement(_motionCount);
          _motionCount = 1.0;
          _lastMeasurementMilliSeconds = millis();
        }
      }
      else
      {

        if (motion == 1)
        {
          _motionCount++;
           _lastdetectionTime = millis();
        }
       
      }
      break;
    }
  }
}
