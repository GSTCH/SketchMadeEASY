//*****************************************************************
//* Class MotorServo360T1 - Header
//*
//* Servo class use INT1
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

#ifndef EASY_MOTORSERVO360T1_H
#define EASY_MOTORSERVO360T1_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldServo360T1.h"

class MotorServo360T1 : public MotorBase {
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY  
  MotorServo360T1(int aId, int aPin)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT1_INDEX)) {
    _motorShield = new MotorShieldServo360T1(aPin);
  }
#endif

  //*************************************
  MotorServo360T1(int aPin)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT1_INDEX)) {
    _motorShield = new MotorShieldServo360T1(aPin);
  }

  //*************************************
#ifdef CREATE_ID_MANUALLY  
  MotorServo360T1(int aId, int aPin, int aMaxForwardMillis, int aStopMillis, int aMaxBackwardMillis)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT1_INDEX)) {
    _motorShield = new MotorShieldServo360T1(aPin, aMaxForwardMillis, aStopMillis, aMaxBackwardMillis);
  }
#endif

  //*************************************
  MotorServo360T1(int aPin, int aMaxForwardMillis, int aStopMillis, int aMaxBackwardMillis)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT1_INDEX)) {
    _motorShield = new MotorShieldServo360T1(aPin, aMaxForwardMillis, aStopMillis, aMaxBackwardMillis);
  }
};

#endif
