//*****************************************************************
//* Class MotorStepperRotateI2C - Header
//*
//* Stepper motor control class use Adafruit motor shield V2 (I2C)
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

#ifndef EASY_MOTORSTEPPERROTATEI2C_H
#define EASY_MOTORSTEPPERROTATEI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldStepperRotateI2C.h"

class MotorStepperRotateI2C : public MotorBase {
public:
  //*************************************
  //* Adafruit MotorShield V2:
  //* aStepperNr : Number of stepper on shield
  //* aResolution : steps per revolution of the stepper motor (without gear) [PPS]
  //* aMaxCylcesPerSecond : Max frequency of the stepper motor [PPS]
  //* aStepStyle : Type of stepper motor signal (ssSingle, ssDouble, ssInterleave, ssMicrostep)
  //* aBusAdddress : I2C Address of the shield    
  MotorStepperRotateI2C(int aStepperNr, int aResolution, int aMaxCylcesPerSecond, EStepStyle aStepStyle = ssSingle, int aBusAdddress = 0x60)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_STEPPERROTATE_INDEX)) {
    _motorShield = new MotorShieldStepperRotateI2C(aStepperNr, aResolution, aMaxCylcesPerSecond, aStepStyle, aBusAdddress);
  }
};
#endif