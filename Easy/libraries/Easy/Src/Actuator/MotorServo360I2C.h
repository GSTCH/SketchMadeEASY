//*****************************************************************
//* Class MotorServo360I2C - Header
//*
//* Servo class use Adafruit Servo/PWM I2C shield
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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

#ifndef EASY_MOTORSERVO360I2C_H
#define EASY_MOTORSERVO360I2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldServo360I2C.h"

class MotorServo360I2C : public MotorBase {
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY
  MotorServo360I2C(int aId, int aServoNr, int aBusAddress)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOI2C_INDEX)) {
    _motorShield = new MotorShieldServo360I2C(aServoNr, aBusAddress);
  }
#endif

  //*************************************
  MotorServo360I2C(int aServoNr, int aBusAddress = 0x40)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOI2C_INDEX)) {
    _motorShield = new MotorShieldServo360I2C(aServoNr, aBusAddress);
  }

  //*************************************
#ifdef CREATE_ID_MANUALLY  
  MotorServo360I2C(int aId, int aServoNr, int aMaxForwardPwm, int aStopPwm, int aMaxBackwardPwm, int aBusAddress)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOI2C_INDEX)) {
    _motorShield = new MotorShieldServo360I2C(aServoNr, aMaxForwardPwm, aStopPwm, aMaxBackwardPwm, aBusAddress);
  }
#endif

  //*************************************
  MotorServo360I2C(int aServoNr, int aMaxForwardPwm, int aStopPwm, int aMaxBackwardPwm, int aBusAddress = 0x40)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOI2C_INDEX)) {
    _motorShield = new MotorShieldServo360I2C(aServoNr, aMaxForwardPwm, aStopPwm, aMaxBackwardPwm, aBusAddress);
  }
};

#endif
