//*****************************************************************
//* Class MotorShieldServo360Pwm - Header
//*
//* Internal class to set command of a servo 360 using a PWM
//*
//* Class changes the PWM frequency from PIN9 and 10 to 50 Hz.
//* After this  pulse width changes by set the register value.
//*
//* https://forum.arduino.cc/t/pwm-to-50-hz/
//* https://tkristner.github.io/blog/Arduino-PWM-AC-50hz/
//* https://microcontrollerslab.com/arduino-pwm-tutorial-generate-fix-and-variable-frequency-signal/
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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

#ifndef EASY_MOTORSHIELDSERVO360PWM_H
#define EASY_MOTORSHIELDSERVO360PWM_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include <Arduino.h>

// A position cannot be specified for a 360° servo.
// Depending on the pulse duration, it turns forwards, backwards or stands still.
// Values have to be adjusted depending on the type.
// For this it exists a constructor with extra parameter, this are the default values.
#define MAX_BACKWARD_PWMVALUE 2000
#define MAX_FORWARD_PWMVALUE 4000
#define STOP_PWMVALUE 3000  // (MIN+MAX)/2
#define MILLIS_PWMRANGE 1000

class MotorShieldServo360Pwm : public MotorShieldBase {
private:
  int _pin;
  int _maxForwardPwm;
  int _stopPwm;
  int _maxBackwardPwm;
  int _pwm;

protected:

public:
  //*************************************
  MotorShieldServo360Pwm(int aPin)
    : MotorShieldBase() {
    _maxForwardPwm = MAX_FORWARD_PWMVALUE;
    _stopPwm = STOP_PWMVALUE;
    _maxBackwardPwm = MAX_BACKWARD_PWMVALUE;

    _pin = aPin;
  }

  //*************************************
  MotorShieldServo360Pwm(int aPin, int aMaxForwardPwm, int aStopPwm, int aMaxBackwardPwm)
    : MotorShieldBase() {
    _maxForwardPwm = aMaxForwardPwm;
    _stopPwm = aStopPwm;
    _maxBackwardPwm = aMaxBackwardPwm;

    _pin = aPin;
  }

  //*************************************
  void Setup() {
    pinMode(_pin, OUTPUT);

    cli();  // stop interrupts.
    TCCR1A = 0;  // reset register bits.
    TCCR1B = 0;  // reset register bits.
    TCNT1 = 0;   // reset register bits.

    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);  //COM1x clear on match, set on bottom
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);     //WGM=14, /8 prescaler
    ICR1 = 39999;                                     //20mS period for timer 1
   
    if (_pin == 9) {
      OCR1A = _stopPwm;
    } else if (_pin == 10) {
      OCR1B = _stopPwm;
    }
    sei();  // re-allow interrupts.
  }

  //*************************************
  void forward(int aSpeed) {
    //_pwm = map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, _stopPwm, _maxForwardPwm);
    _pwm = STOP_PWMVALUE - map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, 0, MILLIS_PWMRANGE);
    if (_pin == 9) {
      OCR1A = _pwm;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("S3PWM OCR1A=%d", OCR1A);
#endif
    } else if (_pin == 10) {
      OCR1B = _pwm;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("S3PWM OCR1B=%d", OCR1B);
#endif
    }
  }

  //*************************************
  void backward(int aSpeed) {
    //_pwm = map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, _stopPwm, _maxBackwardPwm);
    _pwm = STOP_PWMVALUE - map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, 0, MILLIS_PWMRANGE);

    if (_pin == 9) {
      OCR1A = _pwm;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("S3PWM OCR1A=%d", OCR1A);
#endif
    } else if (_pin == 10) {
      OCR1B = _pwm;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("S3PWM OCR1B=%d", OCR1B);
#endif
    }
  }

  //*************************************
  void stop() {
    if (_pin == 9) {
      OCR1A = _stopPwm;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("S3PWM OCR1A=%d", OCR1A);
#endif
    } else if (_pin == 10) {
      OCR1B = _stopPwm;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("S3PWM OCR1B=%d", OCR1B);
#endif
    }
  }
};
#endif