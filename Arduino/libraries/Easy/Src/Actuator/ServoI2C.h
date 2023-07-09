//*****************************************************************
//* Class ServoI2C - Header
//*
//* Servo class use Adafruit servo/PWM shield over I2C
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

#ifndef EASY_SERVOI2C_H
#define EASY_SERVOI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\ServoBase.h"
#include "..\Kernel\ServoShieldI2C.h"

class ServoI2C : public ServoBase {
public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY     
  ServoI2C(int aId, int aMinAngle, int aMaxAngle, int aServoNr, int aBusAddress = 0x40)
    : ServoBase(aId, aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_I2C_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("ST1(%d):C B=%d, A=[%d-%d]", _id,  aBusAddress, aMinAngle, aMaxAngle);
#endif         
    _servoShield = new ServoShieldI2C(aServoNr, aMinAngle, aMaxAngle, aBusAddress);
  }
#endif

  //*************************************
  ServoI2C(int aMinAngle, int aMaxAngle, int aServoNr, int aBusAddress = 0x40)
    : ServoBase(aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_I2C_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("SI2C(%d):C A=[%d-%d], N=%d, B=%d", _id,  aMinAngle, aMaxAngle, aServoNr, aBusAddress);
#endif         
    _servoShield = new ServoShieldI2C(aServoNr, aMinAngle, aMaxAngle, aBusAddress);
  }
};

#endif
