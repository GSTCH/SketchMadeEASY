//*****************************************************************
//* Class ServoT1 - Header
//*
//* Servo class use TIMER INT1
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

#ifndef EASY_SERVOT1_H
#define EASY_SERVOT1_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\ServoBase.h"
#include "..\Kernel\ServoShieldT1.h"

class ServoT1 : public ServoBase {
public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY     
  ServoT1(int aId, int aPin, int aMinAngle, int aMaxAngle)
    : ServoBase(aId, aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_T1_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("ST1(%d):C P=%d, A=[%d-%d]", _id,  aPin, aMinAngle, aMaxAngle);
#endif      
    _servoShield = new ServoShieldT1(aPin, aMinAngle, aMaxAngle);
  }
#endif

  //*************************************
  ServoT1(int aPin, int aMinAngle, int aMaxAngle)
    : ServoBase(aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_T1_INDEX)) {
#ifdef LOG_SETUP
  GetLog()->printf("ST2(%d):C P=%d, A=[%d-%d]", _id,  aPin, aMinAngle, aMaxAngle);
#endif      
    _servoShield = new ServoShieldT1(aPin, aMinAngle, aMaxAngle);
  }
};

#endif
