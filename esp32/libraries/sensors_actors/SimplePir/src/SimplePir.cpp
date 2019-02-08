#include "SimplePir.h"

SimplePir::SimplePir(int pin, int interval, const char *thingName, 
    const char *name, const char *unit, float threshold) : Sensor(thingName, name, unit, threshold)
{
  _pin = pin;
  pinMode(_pin, INPUT);
  _isMotion = digitalRead(_pin);
  _lastMotionDetectedMs = millis();
  _intervalMs = interval * 1000;
}

void SimplePir::measure()
{
  bool isNowMotion = digitalRead(_pin);
  if (!isNowMotion && !_isMotion) {  // keine Änderung
    return;
  }
  if (isNowMotion == true ) {  // neue Bewegung erkannt
    _lastMotionDetectedMs = millis();  // Delay gilt ab jetzt
    if (_isMotion == false) {
      _isMotion=true;
      setMeasurement(1.0);
    }
  }
  else{  // isNowMotion == false && _pirState == true  ==> Zeitablauf
    if (millis() > _lastMotionDetectedMs + _intervalMs) {
      _isMotion = false;
      setMeasurement(0.0);
    }
  }
}
