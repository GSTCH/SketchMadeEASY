//*****************************************************************
//* Class ServoShieldPwm - Header
//*
//* Internal class to set command of a servo using a PWM, usable with PIN9 or PIN10 
//*
//* Class changes the PWM frequency from PIN9 and 10.
//* After this  pulse width changes by set the register value.
//* https://tkristner.github.io/blog/Arduino-PWM-AC-50hz/
//* https://microcontrollerslab.com/arduino-pwm-tutorial-generate-fix-and-variable-frequency-signal/
//* https://forum.arduino.cc/t/50hz-pwm-on-both-pin-9-and-10/930720/5
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
//
//* (C) written in 2023 by Hans Rothenbuehler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************

#ifndef EASY_SERVOSHIELDPWM_H
#define EASY_SERVOSHIELDPWM_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "ServoShieldBase.h"
#include <Arduino.h>

#ifndef EASY_MIN_PWMVALUE
#define EASY_MIN_PWMVALUE 800
#endif

#ifndef EASY_MAX_PWMVALUE
#define EASY_MAX_PWMVALUE 5000
#endif

#ifndef EASY_DEFAULT_PWMVALUE
#define EASY_DEFAULT_PWMVALUE 2900  // (MIN+MAX)/2
#endif

class ServoShieldPwm : public ServoShieldBase {
private:
  int _pin;
  int _minPwm;
  int _maxPwm;
  int _minAngle;
  int _maxAngle;
  
protected:

public:
  //*************************************
  ServoShieldPwm(int aPin, int aMinAngle, int aMaxAngle)
    : ServoShieldBase() {
    _minPwm = EASY_MIN_PWMVALUE;
    _maxPwm = EASY_MAX_PWMVALUE;
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
    _pin = aPin;
  }

  //*************************************
  ServoShieldPwm(int aPin, int aMinAngle, int aMaxAngle, int aMinPwm, int aMaxPwm)
    : ServoShieldBase() {
    _minPwm = aMinPwm;
    _maxPwm = aMaxPwm;
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
    _pin = aPin;
  }

  //*************************************
  void Setup() {
    pinMode(_pin, OUTPUT);
    
    cli();      
    // stop interrupts.
    
    TCCR1A = 0;  // reset register bits.
    TCCR1B = 0;  // reset register bits.
    TCNT1 = 0;   // reset register bits.

    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);  //COM1x clear on match, set on bottom
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);     //WGM=14, /8 prescaler
    ICR1 = 39999;                                     //20mS period for timer 1 

    if (_pin == 9) {
      OCR1A = (_minPwm+_maxPwm)/2;
    } else if (_pin == 10) {
      OCR1B = (_minPwm+_maxPwm)/2;
    }

    sei();  // re-allow interrupts.    
  }

  //*************************************
  void angle(int aAngle) {
    int pwm = map(aAngle, _minAngle, _maxAngle, _minPwm, _maxPwm);
    if (_pin == 9) {
      OCR1A = pwm;
#ifdef LOG_LOOP
      GetLog()->printf("SPWM OCR1A=%d", OCR1A);
#endif
    } else if (_pin == 10) {
      OCR1B = pwm;
#ifdef LOG_LOOP
      GetLog()->printf("SPWM OCR1B=%d", OCR1B);
#endif
    }
  }
};
#endif