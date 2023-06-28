//*****************************************************************
//* Class MotorServo360PWM - Header
//*
//* Servo class use change frequency of PWM signal, Uno R3 only
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

#ifndef EASY_MOTORSERVO360PWM_H
#define EASY_MOTORSERVO360PWM_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldServo360Pwm.h"

class MotorServo360Pwm : public MotorBase {
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY  
  MotorServo360Pwm(int aId, int aPin)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOPWM_INDEX)) {
    _motorShield = new MotorShieldServo360Pwm(aPin);
  }
#endif

  //*************************************
  MotorServo360Pwm(int aPin)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOPWM_INDEX)) {
    _motorShield = new MotorShieldServo360Pwm(aPin);
  }

  //*************************************
#ifdef CREATE_ID_MANUALLY
  MotorServo360Pwm(int aId, int aPin, int aMaxForwardPwm, int aStopPwm, int aMaxBackwardPwm)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOPWM_INDEX)) {
    _motorShield = new MotorShieldServo360Pwm(aPin, aMaxForwardPwm, aStopPwm, aMaxBackwardPwm);
  }
#endif

  //*************************************
  MotorServo360Pwm(int aPin, int aMaxForwardPwm, int aStopPwm, int aMaxBackwardPwm)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOPWM_INDEX)) {
    _motorShield = new MotorShieldServo360Pwm(aPin, aMaxForwardPwm, aStopPwm, aMaxBackwardPwm);
  }

  
};

#endif
