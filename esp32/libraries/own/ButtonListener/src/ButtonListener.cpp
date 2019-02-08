#include "ButtonListener.h"

#include <Arduino.h>

ButtonListenerClass::ButtonListenerClass(uint8_t pin, uint8_t puEnable, uint8_t invert, uint32_t dbTime) :
 _myButton(pin, puEnable, invert, dbTime){}

void ButtonListenerClass::setCallback(void(*callback)(int)){
    _callback = callback;
}

void ButtonListenerClass::listen(){
    buttonEventListener();
}

void ButtonListenerClass::buttonEventListener(){
    static bool longPress = false;
    static unsigned long triggerTime = 0;
    static int pressCount = 0;

    _myButton.read();
    if(_myButton.pressedFor(_long_press_interval) && !longPress){
        longPress = true;
    }
    if(_myButton.wasReleased()){
        if(longPress){
            _callback(BUTTON_LISTENER_LONG);
        }else{
            if(triggerTime == 0){
                triggerTime = millis();
                pressCount = 1;
            }else{
                pressCount++;
            }
        }
        longPress = false;
    }
    
    if(millis() - triggerTime > _multi_press_interval && triggerTime != 0){
        if(pressCount == 1){
            _callback(BUTTON_LISTENER_SIMPLE);
        }else{
            _callback(BUTTON_LISTENER_MULTI);
        }

        triggerTime = 0;
    }
}