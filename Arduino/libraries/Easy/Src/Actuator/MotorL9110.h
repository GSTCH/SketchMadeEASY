//*****************************************************************
//* Class MotorL9110 - Header
//*
//* Motor controlled by an L9110h chip
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

#ifndef EASY_MOTORL9110_H
#define EASY_MOTORL9110_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldL9110.h"

class MotorL9110 : public MotorBase {
private:
protected:
public:
#ifdef CREATE_ID_MANUALLY
  MotorL9110(int aId, int aPinA, int aPinB)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_L9110_INDEX)) {
    _motorShield = new MotorShieldL9110(aPinA, aPinB);
  }
#endif
  
  MotorL9110(int aPinA, int aPinB)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_L9110_INDEX)) {
    _motorShield = new MotorShieldL9110(aPinA, aPinB);
  }
};

#endif