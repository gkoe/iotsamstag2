# Library StateMachine

## Ziele

Abstrakte Basisklasse zur Verwaltung der allgemeingültigen Daten und Verhaltens von Sensoren. Die aber von Sensor erbt. 
Jeder StateMachine ist innerhalb des Thing über ID eindeutig identifizierbar. Er liefert seinen Messwert automatisch per Log an den Server, wenn er sich um eine per Parameter festgelegte Schwelle geändert hat. Danach geht er in einen Modus wo er nach einent voreingestellt interval den Mittelwert sendet. Er meldet seinen Messwert aber zumindest alle 15 Minuten. 

## Software

### Abhängigkeiten

- Logger
- Sensor


### Testanwendung am ESP32

Die Klasse StateMachine wird über das Testprogramm der Library Thing mitgetestet.


#### Library


#### Headerdatei StateMachine.h

````c
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
````

### Beispiel für einen konkreten Lautstärkesensor

Am Beispiel des Lautstärkesensor KY-037 wird die Verwendung der Klasse StateMachine demonstriert.

Der Lautstärkesensor leitet von der Klasse StateMachine ab und überschreibt die Methode zum Ermitteln des Messwertes.

````c
#include <Arduino.h>
#include <math.h>
#include <KY_037.h>

KY_037 *ky_037;
  
void setup ()
{
  Serial.begin (115200); 
	ky_037 = new KY_037(12, 13, 30, "test", "test", "db", 5.0);
}
  
void loop ()
{
	ky_037->getMeasure();
	delay(100);
}
````

Die Implementierung benötigt ebenfalls nur einige Zeilen Code

````c
KY_037::KY_037( uint8_t dpin, uint8_t apin, uint8_t interval, const char* thingName,  const char* name, const char* unit, float threshold)
	: StateMachine(interval, thingName, name, unit, threshold)
{
	pinMode (dpin, INPUT);
 	pinMode (apin, INPUT);
	_dpin = dpin;
	_apin = apin;
}

float KY_037::getMeasure() {
  int digital, analog;
	float result;
	analog = analogRead (_apin); 
	if(analog >= 196){
  	digital = digitalRead (_dpin);
		result = 20 * log10((analog/4)+pow((analog-196), 3));
		Serial.println(result);
		return result;
	}
	return -1;
}
````
