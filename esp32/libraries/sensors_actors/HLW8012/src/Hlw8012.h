#pragma once
#include <Arduino.h>
#include <Sensor.h>
/*
    Erfassung der Leistung über einen HLW8012

    Dabei wird von einer Spannung von 230V und ohmscher Last ausgegangen und die Spannung nicht gemessen.
    Damit kann der SEL-PIN fix auf Strommessung geschaltet werden.
    Die Spannungs- und echte Leistungsmessung des Bausteins wird nicht verwendet, damit die
    Abfragezeiten überschaubar bleiben.
       
    Interface des HLW8012
      Output CF1 ==> PWM-Signal für Spannung/Strom
      Input SEL ==> 0=Strom, 1=Spannung  wird fix auf HIGH gelegt ==> Strommessung
      Output CF ==> Leistung (wird bei dieser Bibliothek nicht verwendet)
    
    Funktion des HLW8012
      Der Sensor codiert den Messwert (Strom, Spannung, Leistung) in die Zyklusdauer des PWM-Signals.
      Je kürzer die Zeit zwischen zwei steigenden Flanken, desto höher der Messwert. 
      Messwert 0 hat daher die längste Zykluszeit (>250ms  => ca. 4Hz). Bei kleinen Strömen ist
      die Genauigkeit gering.
      Jede steigende Flanke löst einen Interrupt aus. Die zugehörige ISR legt den Zeitstempel
      in einen Ringpuffer ab. Bei der Abfrage des Stromwertes (mit 230V auf Leistung umgerechnet) werden
      die Zeitintervalle aus dem Ringpuffer verwendet und in den Messwert umgerechnet.
*/

class Hlw8012 : public Sensor
{
  public:
    Hlw8012(const uint8_t cf1Pin, const uint8_t selPin,const char *thingName, const char *name, const char *unit, float threshold);
    float getPower();
  private:
  virtual void measure();
};

