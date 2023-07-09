//*****************************************************************
//* Class MotorShieldL9110 - Header
//*
//* Internal class to set command of a motor with a L9110 shield
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

#ifndef EASY_MOTORSHIELDL9110_H
#define EASY_MOTORSHIELDL9110_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include <Arduino.h>

class MotorShieldL9110 : public MotorShieldBase {
private:
  int _pinA;
  int _pinB;

protected:

public:
  //*************************************
  //* aPinA : PWM Pin, forward
  //* aPinB : PWM Pin, backward
  MotorShieldL9110(int aPinA, int aPinB)
    : MotorShieldBase() {
    _pinA = aPinA;
    _pinB = aPinB;
  }

  //*************************************
  void Setup() {
    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
  }

  //*************************************
  //* aSpeed [1...255]
  void forward(int aSpeed) {
    // Set pin to forward
    analogWrite(_pinA, aSpeed);
    digitalWrite(_pinB, LOW);
  }

  //*************************************
  //* aSpeed [1...255]
  void backward(int aSpeed) {
    // Set pin to backward
    digitalWrite(_pinA, LOW);
    analogWrite(_pinB, aSpeed);
  }

  //*************************************
  void stop() {
    // Set pin to stop
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, LOW);
  }
};
#endif