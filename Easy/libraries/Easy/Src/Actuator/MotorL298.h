//*****************************************************************
//* Class MotorL298 - Header
//*
//* Motor controlled by an L298 chip
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

#ifndef EASY_MOTORL298_H
#define EASY_MOTORL298_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldL298.h"

class MotorL298 : public MotorBase {
private:
protected:
public:
#ifdef CREATE_ID_MANUALLY
  MotorL298(int aId, int aDirectionPin, int aSpeedPin)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_L298_INDEX)) {
    _motorShield = new MotorShieldL298(aDirectionPin, aSpeedPin);
  }
#endif

  MotorL298(int aDirectionPin, int aSpeedPin)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_L298_INDEX)) {
    _motorShield = new MotorShieldL298(aDirectionPin, aSpeedPin);
  }
};

#endif