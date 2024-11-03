//*****************************************************************
//* Class MotorShieldServo360T1 - Header
//*
//* Internal class to set command of a servo 360 using Timer1
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

#ifndef EASY_MOTORSHIELDSERVO360T1_H
#define EASY_MOTORSHIELDSERVO360T1_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#ifndef ARDUINO_ARCH_ESP32
#include <Servo.h>
#else
#include <ESP32Servo.h>
#endif


// A position cannot be specified for a 360 ° servo.
// Depending on the pulse duration, it turns forwards, backwards or stands still.
// Values have to be adjusted depending on the type.
// For this it exists a constructor with extra parameter, this are the default values.
#ifndef MILLIS_MAX_FORWARD_T1
#define MILLIS_MAX_FORWARD_T1 1000
#endif

#ifndef MILLIS_STOP_T1
#define MILLIS_STOP_T1 1500
#endif

#ifndef MILLIS_MAX_BACKWARD_T1
#define MILLIS_MAX_BACKWARD_T1 2000
#endif

class MotorShieldServo360T1 : public MotorShieldBase {
private:
  int _pin;
  int _maxForwardMillis;
  int _stopMillis;
  int _maxBackwardMillis;
  Servo _servo360;

protected:

public:
  //*************************************
  MotorShieldServo360T1(int aPin)
    : MotorShieldBase() {
    _maxForwardMillis = MILLIS_MAX_FORWARD_T1;
    _stopMillis = MILLIS_STOP_T1;
    _maxBackwardMillis = MILLIS_MAX_BACKWARD_T1;

    _pin = aPin;
  }

  //*************************************
  MotorShieldServo360T1(int aPin, int aMaxForwardMillis, int aStopMillis, int aMaxBackwardMillis)
    : MotorShieldBase() {
    _maxForwardMillis = aMaxForwardMillis;
    _stopMillis = aStopMillis;
    _maxBackwardMillis = aMaxBackwardMillis;

    _pin = aPin;
  }

  //*************************************
  void Setup() {
    _servo360.attach(_pin);
    delay(100);
    stop();
  }

  //*************************************
  void forward(int aSpeed) {
long val = _stopMillis + map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, 0, _stopMillis-_maxForwardMillis);
#ifdef _LOG_LOOP_DEBUG
    GetLog()->printf("S3T1:F Spd=%d, Val=%d", aSpeed, val);
#endif
    _servo360.writeMicroseconds(val);
  }

  //*************************************
  void backward(int aSpeed) {
long val = _stopMillis - map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, 0, _maxBackwardMillis-_stopMillis);
#ifdef _LOG_LOOP_DEBUG
    GetLog()->printf("S3T1:B Spd=%d, Val=%d", aSpeed, val);
#endif
    _servo360.writeMicroseconds(val);
  }

  //*************************************
  void stop() {
    _servo360.writeMicroseconds(_stopMillis);
  }
};
#endif