//*****************************************************************
//* Class EncoderMotorL298 - Header
//*
//* EncoderMotor controlled by an L298 chip
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

#ifndef EASY_ENCODERMOTORL298_H
#define EASY_ENCODERMOTORL298_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\EncoderMotorBase.h"
#include "..\Kernel\MotorShieldL298.h"

class EncoderMotorL298 : public EncoderMotorBase {
private:
protected:
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY
  EncoderMotorL298(int aId, int aDirectionPin, int aSpeedPin, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed )
    : EncoderMotorBase(aId, CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L298_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed) {
    _motorShield = new MotorShieldL298(aDirectionPin, aSpeedPin);
  }
#endif

  //*************************************
  EncoderMotorL298(int aDirectionPin, int aSpeedPin, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed)
    : EncoderMotorBase(CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L298_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed) {
    _motorShield = new MotorShieldL298(aDirectionPin, aSpeedPin);
  }
};

#endif