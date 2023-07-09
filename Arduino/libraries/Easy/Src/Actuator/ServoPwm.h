//*****************************************************************
//* Class ServoPWM - Header
//*
//* Servo class PWM with frequency change of PWM, only UNO R3
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

#ifndef EASY_SERVOPWM_H
#define EASY_SERVOPWM_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\ServoBase.h"
#include "..\Kernel\ServoShieldPwm.h"

class ServoPwm : public ServoBase {
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY     
  ServoPwm(int aId, int aPin, int aMinAngle, int aMaxAngle)
    : ServoBase(aId, aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_PWM_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("SPW(%d):C P=%d, A=[%d-%d]", _id,  aPin, aMinAngle, aMaxAngle);
#endif         
    _servoShield = new ServoShieldPwm(aPin, aMinAngle, aMaxAngle);
  }
#endif

  //*************************************
  ServoPwm(int aPin, int aMinAngle, int aMaxAngle)
    : ServoBase(aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_PWM_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("SPW(%d):C P=%d, A=[%d-%d]", _id,  aPin, aMinAngle, aMaxAngle);
#endif         
    _servoShield = new ServoShieldPwm(aPin, aMinAngle, aMaxAngle);
  }
};

#endif
