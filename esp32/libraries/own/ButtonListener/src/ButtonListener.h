#pragma once

#include <Button.h>

#define BUTTON_LISTENER_LONG 0
#define BUTTON_LISTENER_SIMPLE 1
#define BUTTON_LISTENER_MULTI 2

class ButtonListenerClass{

    typedef void(*ButtonListenerCallback)(int); 

    public: 
        ButtonListenerClass(uint8_t pin, uint8_t puEnable, uint8_t invert, uint32_t dbTime);
        void listen();
        void setCallback(ButtonListenerCallback callback);
    protected:
        Button _myButton;

        ButtonListenerCallback _callback;

        void buttonEventListener();
        int _long_press_interval = 1000;
        int _multi_press_interval = 200;
};

typedef ButtonListenerClass ButtonListener;