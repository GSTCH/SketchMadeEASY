//*****************************************************************
//* Class ServoT2 - Header
//*
//* Servo class use TIMER INT2
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

#ifndef EASY_SERVOT2_H
#define EASY_SERVOT2_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\ServoBase.h"
#include "..\Kernel\ServoShieldT2.h"

class ServoT2 : public ServoBase {
public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY     
  ServoT2(int aId, int aPin, int aMinAngle, int aMaxAngle)
    : ServoBase(aId, aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_T2_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("ST2(%d):C P=%d, A=[%d-%d]", _id,  aPin, aMinAngle, aMaxAngle);
#endif      
    _servoShield = new ServoShieldT2(aPin, aMinAngle, aMaxAngle);
  }
#endif

  //*************************************
  ServoT2(int aPin, int aMinAngle, int aMaxAngle)
    : ServoBase(aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_T2_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("ST2(%d):C P=%d, A=[%d-%d]", _id,  aPin, aMinAngle, aMaxAngle);
#endif      
    _servoShield = new ServoShieldT2(aPin, aMinAngle, aMaxAngle);
  }
};

#endif
