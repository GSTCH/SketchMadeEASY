//*****************************************************************
//* Class MotorI2C - Header
//*
//* Adafruit Motor Shield Version 2:
//* It's the only motor shield to control 4 (or more) motors with an UNO
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

#ifndef EASY_MOTORI2C_H
#define EASY_MOTORI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\MotorBase.h"
#include "..\Kernel\MotorShieldAdafruitV2.h"

class MotorI2C : public MotorBase {
private:

public:
#ifdef CREATE_ID_MANUALLY
  MotorI2C(int aId, int aMotorNr, int aBusAdddress)
    : MotorBase(aId, CreateElementId(EbtActuator, EkaMotor, MOTOR_I2C_INDEX)) {
    _motorShield = new CMotorShieldAdafruitV2(aMotorNr, aBusAdddress);
  }
#endif

  MotorI2C(int aMotorNr, int aBusAdddress = 0x60)
    : MotorBase(CreateElementId(EbtActuator, EkaMotor, MOTOR_I2C_INDEX)) {
    _motorShield = new MotorShieldAdafruitV2(aMotorNr, aBusAdddress);
  }
};

#endif