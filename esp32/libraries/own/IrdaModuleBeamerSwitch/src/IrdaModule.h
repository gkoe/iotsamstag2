
#pragma once

#include <Arduino.h>
#include <Actor.h>

class IrdaModule : public Actor
{
  public:
        IrdaModule(int rxPin, int txPin, const char *thingName, const char *name);
        void read_ir_signal();
        void start_learning_mode();
        void send_ir_signal(char *irCodedefault);

        virtual void setActorTo(float value);
        virtual float readStateFromActor();

  private:
      HardwareSerial* _hardwareSerialPtr;
      float _beamerstate;

};