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

#include "Display.h"

DisplayClass::DisplayClass(uint8_t _address, uint8_t _sda, uint8_t _scl): 
    _display(_address, _sda, _scl, GEOMETRY_128_64){  // GEOMETRY_128_64
    for(int i = 0; i < DISPLOG_BUFFER_HEIGHT; i++){
        Serial.println(String(_buffer[i]));
        _buffer[i][DISPLOG_BUFFER_WIDTH] = 0;
    }
}

void DisplayClass::init(uint8_t animation, bool printToSerial, uint8_t to_long_behaviour, uint8_t lineHeight){
    
    _to_long_behaviour = to_long_behaviour;
    _print_to_serial = printToSerial;
    _anim = animation;
    _lineHeight = lineHeight;
    
    _display.init();
    _display.flipScreenVertically();
    _display.setFont(ArialMT_Plain_10);
    _dispWidth = _display.getWidth();
    _dispHeight = _display.getHeight();
}

DisplayClass::~DisplayClass() {}

void DisplayClass::newLine(){
    _lastLine ++;                                   //! wie werden die anderen Zeilen nach oben geschoben?
    if(_lastLine >= DISPLOG_BUFFER_HEIGHT){
        _lastLine = 0;
    }
    for(int i = 0; i < DISPLOG_BUFFER_WIDTH; i++){
        _buffer[_lastLine][i] = 0;
    }
    if(_anim == ANIMATION_NONE){
        _animPX = 0;
        _animFrameStride = _lineHeight;
        _animFrameLength = 0;
    }else if(_anim == ANIMATION_FAST){
        _animPX = _lineHeight;
        _animFrameStride = 2;
        _animFrameLength = 1;
    }else if(_anim == ANIMATION_VERYFAST){
        _animPX = _lineHeight;
        _animFrameStride = 4;
        _animFrameLength = 1;
    }else if(_anim == ANIMATION_MEDIUM){
        _animPX = _lineHeight;
        _animFrameLength = 1;
        _animFrameStride = 1;
    }else if(_anim == ANIMATION_SLOW){
        _animPX = _lineHeight;
        _animFrameLength = 20;
        _animFrameStride = 1;
    }
}

void DisplayClass::carriageReturn(){
    _cursorX = 0;
}

void DisplayClass::nlcr(){
    newLine();
    carriageReturn();
}

size_t DisplayClass::write(uint8_t c){
    if(_print_to_serial){
        Serial.print((char)c);
    }
    if(c == '\n'){
        newLine();
    }else if(c == '\r'){
        carriageReturn();
    }else if(c >= 32){          // druckbares Zeichen
        if(_cursorX >= DISPLOG_BUFFER_WIDTH){  // Zeile ist länger als Zeilenpuffer ==> auf jeden Fall Zeilenumbruch, sonst gäbe es IndexOutOfRange
            nlcr();
        }
        _buffer[_lastLine][_cursorX] = c;
        _cursorX++;
        if(_display.getStringWidth(_buffer[_lastLine], _cursorX) > _dispWidth){
            if(_to_long_behaviour == TO_LONG_BEHAVIOUR_NEWLINE){  // Display Zeilenende erreicht ==> Zeilenumbruch
                _buffer[_lastLine][_cursorX-1] = 0;
                nlcr();
                _buffer[_lastLine][_cursorX] = c;
                _cursorX++;
            }else if(_to_long_behaviour == TO_LONG_BEHAVIOUR_TRIM){  // Display Zeilenende erreicht ==> Cursor stehen lassen
                _cursorX--;
                _buffer[_lastLine][_cursorX] = 0;
            }
        }
        flushToDisplay();
    }
    return 1;
}

void DisplayClass::flushToDisplayOffs(uint8_t offs){
    
}

void DisplayClass::flushToDisplay(){
    do{
        if(_animPX > 0){        
            _animPX-=_animFrameStride;
            delay(_animFrameLength);
        }
        if(_animPX < 0){
            _animPX = 0;
        }
        int y = _dispHeight;
        int curs = _lastLine;
        _display.clear();
        for(int i = 0; i < 10000; i++){ //WHILE TRUE
            y -= _lineHeight;
            if(y < -_lineHeight){
                break;
            }
            if(curs < 0){
                curs = DISPLOG_BUFFER_HEIGHT-1;
            }
            _display.drawString(0, y+_animPX, String(_buffer[curs]));
            curs--;
            if(curs == _lastLine){
                break;
            }
        }
        _display.display();
    }while(_animPX > 0);
}

size_t DisplayClass::write(const uint8_t *buffer, size_t size){
    for(int i = 0; i < size; i++){
        write(buffer[i]);
    }
    return 1;
}

DisplayClass Display;