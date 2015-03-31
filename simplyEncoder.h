/*
                               _                
 ___  _   _  _ __ ___    ___  | |_  ___   _   _ 
/ __|| | | || '_ ` _ \  / _ \ | __|/ _ \ | | | |
\__ \| |_| || | | | | || (_) || |_| (_) || |_| |
|___/ \__,_||_| |_| |_| \___/  \__|\___/  \__, |
                                          |___/ 
generic simple encoder Library
----------------------------------------
A fast C library for encoders, simple, work for most rotary encoders
and not use any direct port manipulation, timer, etc.
version 2.1
coded by Max MC Costa
--------------------------------------------------------
Library works with most arduino compatible processors and teensy3
BUGLIST

*/
#ifndef simplyEncoder_H
#define simplyEncoder_H

#include "Arduino.h"

class simplyEncoder {
  public:
  //2 type of deconding schemes. For most use decoderType=0 but for ebe high resolution use 1
  //pullup must be set false if you already have pullup resistors on encoder!
    void setup(const uint8_t a, const uint8_t b,bool pullup=true, uint8_t decoderType=0);
    int read();

    inline int getCount() const { return _count; }
    inline uint8_t getPinA() const { return _pinA; }
    inline uint8_t getPinB() const { return _pinA; }
    
  private:
    uint8_t _pinA;
    uint8_t _pinB;
    int _state;
    int _prevState;
    int _count;
    int _cycleCount;
	uint8_t		_decoding;
    static const uint8_t cwA[];                           
    static const uint8_t ccwA[];    
    static const uint8_t cwB[];                           
    static const uint8_t ccwB[];  
};

#endif
