//*****************************************************************
//* Class MotorStepperRotate - Header
//*
//* Stepper motor control class use AccelStepper-Library.
//* Different chipls like L298n or L9110h are supported.
//* Details read https://www.airspayce.com/mikem/arduino/AccelStepper/
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

#ifndef EASY_MOTORSTEPPERROTATE_H
#define EASY_MOTORSTEPPERROTATE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldStepperRotate.h"

class MotorStepperRotate : public MotorBase {
public:
  //*************************************
  MotorStepperRotate(int aPin1, int aPin2, int aPin3, int aPin4, int aResolution, EMotorInterfaceType aMotorInterfaceType = miFull4Wire)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_STEPPERROTATE_INDEX)) {
    _motorShield = new MotorShieldStepperRotate(aPin1, aPin2, aPin3, aPin4, aResolution, aMotorInterfaceType);
  }

  //*************************************
  MotorStepperRotate(int aPin1, int aPin2, int aPin3, int aPin4, int aResolution, int aMaxCylcesPerSecond, EMotorInterfaceType aMotorInterfaceType = miFull4Wire)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_STEPPERROTATE_INDEX)) {
    _motorShield = new MotorShieldStepperRotate(aPin1, aPin2, aPin3, aPin4, aResolution, aMaxCylcesPerSecond, aMotorInterfaceType);
  }
};
#endif