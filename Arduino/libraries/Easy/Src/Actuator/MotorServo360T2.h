//*****************************************************************
//* Class MotorServo360T2 - Header
//*
//* Servo class use INT2
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

#ifndef EASY_MOTORSERVO360T2_H
#define EASY_MOTORSERVO360T2_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldServo360T2.h"

class MotorServo360T2 : public MotorBase {
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY   
  MotorServo360T2(int aId, int aPin)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT2_INDEX)) {
    _motorShield = new MotorShieldServo360T2(aPin);
  }
#endif

  //*************************************
  MotorServo360T2(int aPin)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT2_INDEX)) {
    _motorShield = new MotorShieldServo360T2(aPin);
  }

  //*************************************
#ifdef CREATE_ID_MANUALLY   
  MotorServo360T2(int aId, int aPin, int aMaxForwardMillis, int aStopMillis, int aMaxBackwardMillis)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT2_INDEX)) {
    _motorShield = new MotorShieldServo360T2(aPin, aMaxForwardMillis, aStopMillis, aMaxBackwardMillis);
  }
#endif

  //*************************************
  MotorServo360T2(int aPin, int aMaxForwardMillis, int aStopMillis, int aMaxBackwardMillis)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT2_INDEX)) {
    _motorShield = new MotorShieldServo360T2(aPin, aMaxForwardMillis, aStopMillis, aMaxBackwardMillis);
  }
};

#endif
