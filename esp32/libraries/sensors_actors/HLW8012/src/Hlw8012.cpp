#include "Hlw8012.h"

//#define HLW8012_DEBUG

//--------------------------------------------------------------------------------------//
// Statische Variablen (Ringpuffer samt Index) und statische ISR

#define TIMESTAMPS 10  // Zuerst eine Startsequenz und dann 80 Bits
unsigned long __risingEdgeMicroSeconds[TIMESTAMPS];
volatile uint8_t __risingEdgeIndex=0;

/*
    Statische Methode, die als ISR verwendet wird.
*/
static void __notifyRisingEdgeStatic(){
    __risingEdgeIndex++;
    if(__risingEdgeIndex >= TIMESTAMPS) __risingEdgeIndex=0;
    __risingEdgeMicroSeconds[__risingEdgeIndex]=micros();
}
//--------------------------------------------------------------------------------------//

Hlw8012::Hlw8012(const uint8_t cf1Pin, const uint8_t selPin,const char *thingName, const char *name, const char *unit, float threshold) 
    : Sensor(thingName, name, unit, threshold)
{
  pinMode(cf1Pin, INPUT_PULLUP);    // cf1-PIN wird zur PWM-Messung per ISR verwendet
  digitalWrite(cf1Pin, HIGH );
  pinMode(selPin, OUTPUT);
  digitalWrite(selPin, HIGH);
  // Zeitstempel alle auf ungültig setzen (-1)
  for(int i=0; i<TIMESTAMPS; i++){
    __risingEdgeMicroSeconds[i]=-1;
  }
  // ISR auf steigende Flanke des PWM-Signals setzen
  attachInterrupt(digitalPinToInterrupt(cf1Pin), __notifyRisingEdgeStatic, RISING);
  delayMicroseconds(10);  // Delay a bit to let sensor pull data line low.
}

/**
 * PWM-Zeiten analysieren und daraus die Leistung ermitteln
 */
float Hlw8012::getPower(){
  long sum = 0;
  int count = 0;
  int index = __risingEdgeIndex;
  long timestamp = __risingEdgeMicroSeconds[index];
  index--;
  if(index < 0) index = TIMESTAMPS-1;
  while(count+1 < TIMESTAMPS && __risingEdgeMicroSeconds[index] != -1){
    long delta = timestamp-__risingEdgeMicroSeconds[index];
    if(delta <0 ){  // ISR hat den Index schon wieder beschrieben
      break;
    }
    count++;
    sum += delta;
    timestamp = __risingEdgeMicroSeconds[index];
    #ifdef HLW8012_DEBUG
      Serial.print(delta);
      Serial.print(";");
      // Serial.print("*HL Timestamp: ");
      // Serial.print(timestamp);
      // Serial.print(", Index: ");
      // Serial.println(index);
    #endif    
    index--;
    if(index < 0) index = TIMESTAMPS-1;
  }
  if(count == 0) return -1.0;
  float avg = ((float)sum)/count/1000;
  float power = 1.5*1000/avg;
  #ifdef HLW8012_DEBUG
     Serial.print(count);
     Serial.print(";");
     Serial.print(sum);
     Serial.print(";");
     Serial.println(power);
  #endif    
  if(power < 10.0){
    return 0.0;
  }
  return power;
}


void Hlw8012::measure()
{
  float power = getPower();
  setMeasurement(power);
}


