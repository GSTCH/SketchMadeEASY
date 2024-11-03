//*****************************************************************
//* Class ServoShieldT1 - Header
//*
//* Internal class to set command of a servo using Timer1
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

#ifndef EASY_SERVOSHIELDT1_H
#define EASY_SERVOSHIELDT1_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "ServoShieldBase.h"
#ifndef ARDUINO_ARCH_ESP32
#include <Servo.h>
#else
#include <ESP32Servo.h>
#endif
#include <Arduino.h>

class ServoShieldT1 : public ServoShieldBase {
private:
  int _pin;
  int _minAngle;
  int _maxAngle;
  Servo _servo;

protected:

public:
  //*************************************
  ServoShieldT1(int aPin, int aMinAngle, int aMaxAngle)
    : ServoShieldBase() {
    _pin = aPin;
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
  }

  //*************************************
  void Setup() {
    _servo.attach(_pin);
    delay(100);
    _servo.write((_maxAngle + _minAngle) / 2);
  }

  //*************************************
  void angle(int aAngle) {
    _servo.write(map(aAngle, _minAngle, _maxAngle, 0, 180));
  }
};
#endif