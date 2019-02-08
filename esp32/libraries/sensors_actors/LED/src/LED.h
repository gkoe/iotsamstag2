#pragma once
#include <Arduino.h>
#include <Actor.h>
#include <stdint.h>
#include <esp32_digital_led_lib.h>

class LED : public Actor 
{
	public:
		LED(int pin, int pixels, const char* thingName, const char* name);
		virtual void setActorTo(float value);
		virtual float readStateFromActor();
		void rainbow(unsigned long delay_ms, unsigned long timeout_ms);
		void scanner(unsigned long delay_ms, unsigned long timeout_ms);
		void scanner(pixelColor_t scanColors, unsigned long delay_ms, unsigned long timeout_ms);

	private:
		void scanners(strand_t * strands[], pixelColor_t scanColors, int numStrands, unsigned long delay_ms, unsigned long timeout_ms);
		void rainbows(strand_t * strands[], int numStrands, unsigned long delay_ms, unsigned long timeout_ms);
		void staticLight(pixelColor_t color);
		int _pin;
		int _pixels;
		strand_t _pStrand;
};
