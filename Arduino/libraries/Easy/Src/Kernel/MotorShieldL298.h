//*****************************************************************
//* Class MotorShieldL298 - Header
//*
//* Internal class to set command of a motor with a L298 shield
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

#ifndef EASY_MOTORSHIELDL298_H
#define EASY_MOTORSHIELDL298_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include <Arduino.h>

class MotorShieldL298 : public MotorShieldBase {
private:
  int _directionPin;
  int _speedPin;

protected:

public:
  //*************************************
  //* aDirectionPin : Digital Output
  //* aSpeedPin : PWM Output
  MotorShieldL298(int aDirectionPin, int aSpeedPin)
    : MotorShieldBase() {
    _directionPin = aDirectionPin;
    _speedPin = aSpeedPin;
  }

  //*************************************
  void Setup() {
    pinMode(_directionPin, OUTPUT);
    pinMode(_speedPin, OUTPUT);
  }

  //*************************************
  //* aSpeed [1...255]
  void forward(int aSpeed) {
    digitalWrite(_directionPin, HIGH);
    analogWrite(_speedPin, aSpeed);
  }

  //*************************************
  //* aSpeed [1...255]
  void backward(int aSpeed) {
    digitalWrite(_directionPin, LOW);
    analogWrite(_speedPin, aSpeed);
  }

  //*************************************
  void stop() {
    digitalWrite(_directionPin, LOW);
    analogWrite(_speedPin, LOW);
  }
};
#endif