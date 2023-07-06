//*****************************************************************
//* Class ServoShieldT2 - Header
//*
//* Internal class to set command of a servo using Timer2
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
//
//* (C) written in 2023 by Hans Rothenbühler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************

#ifndef EASY_SERVOSHIELDT2_H
#define EASY_SERVOSHIELDT2_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "ServoShieldBase.h"
#include <ServoTimer2.h>

#ifndef EASY_PULSE_WIDTH_MIN_MILLIS
#define EASY_PULSE_WIDTH_MIN_MILLIS 750
#endif

#ifndef EASY_PULSE_WIDTH_MAX_MILLIS
#define EASY_PULSE_WIDTH_MAX_MILLIS 2250
#endif

class ServoShieldT2 : public ServoShieldBase {
private:
  int _pin;
  int _minAngle;
  int _maxAngle;
  int _minPulseWidthMillis;
  int _maxPulseWidthMillis;

  ServoTimer2 _servo;

protected:

public:
  //*************************************
  ServoShieldT2(int aPin, int aMinAngle, int aMaxAngle)
    : ServoShieldBase() {
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
    _minPulseWidthMillis = EASY_PULSE_WIDTH_MIN_MILLIS;
    _maxPulseWidthMillis = EASY_PULSE_WIDTH_MAX_MILLIS;
    _pin = aPin;
  }

  //*************************************
  ServoShieldT2(int aPin, int aMinAngle, int aMaxAngle, int aMinPulseWidthMillis, int aMaxPulseWidthMillis)
    : ServoShieldBase() {
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
    _minPulseWidthMillis = aMinPulseWidthMillis;
    _maxPulseWidthMillis = aMaxPulseWidthMillis;
    _pin = aPin;
  }

  //*************************************
  void Setup() {
    _servo.attach(_pin);
    delay(100);
    _servo.write((_maxAngle + _minAngle) / 2);
  }

  //*************************************
  void angle(int aAngle) {
    _servo.write(map(aAngle, _minAngle, _maxAngle, _minPulseWidthMillis, _maxPulseWidthMillis));
  }
};
#endif