/*
MIT License

Copyright (c) 2018 Erik "Obyoxar" Mayrhofer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <SSD1306.h>

#define DISPLOG_BUFFER_HEIGHT 10
#define DISPLOG_BUFFER_WIDTH 23     //! reicht meines Erachtens

#define TO_LONG_BEHAVIOUR_NEWLINE 0
#define TO_LONG_BEHAVIOUR_TRIM 1

#define ANIMATION_NONE 0
#define ANIMATION_FAST 2
#define ANIMATION_VERYFAST 1
#define ANIMATION_MEDIUM 2
#define ANIMATION_SLOW 20

/**
 * 
 */
class DisplayClass : public Print
{
  public:
    /**
   * OLED ist fix am ESP32 verbaut. Daher können die Konfigurationsdaten konstant
   * im Konstruktor vergeben werden.
   */
    DisplayClass(uint8_t _address = 0x3c, uint8_t _sda = 5, uint8_t _scl = 4);

    /**
     * 
     */
    void init(uint8_t animation = ANIMATION_FAST, bool printToSerial = true, 
                uint8_t to_long_behaviour = TO_LONG_BEHAVIOUR_NEWLINE, uint8_t lineHeight = 10);

    ~DisplayClass();
    size_t write(uint8_t) override;
    size_t write(const uint8_t *buffer, size_t size) override;

  protected:
    void newLine();
    void carriageReturn();
    void nlcr();
    void flushToDisplay();
    void flushToDisplayOffs(uint8_t offset);
    char _buffer[DISPLOG_BUFFER_HEIGHT][DISPLOG_BUFFER_WIDTH + 1];
    int8_t _lastLine = 0;
    int16_t _dispWidth;
    int16_t _dispHeight;
    int16_t _cursorX = 0;
    int16_t _cursorY = 0;
    int8_t _lineHeight = 10;
    int8_t _anim;
    int8_t _animFrameLength;
    int8_t _animFrameStride;
    int8_t _animPX = 0;
    uint8_t _to_long_behaviour = TO_LONG_BEHAVIOUR_NEWLINE;
    SSD1306 _display;
    int8_t _bufferIndex;
    bool _print_to_serial;
};

extern DisplayClass Display;