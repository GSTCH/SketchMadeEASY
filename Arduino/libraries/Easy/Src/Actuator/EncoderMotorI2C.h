//*****************************************************************
//* Class EncoderMotorI2C - Header
//*
//* Adafruit Motor Shield Version 2:
//* It's the only motor shield to control 4 (or more) motors with an UNO
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#ifndef EASY_ENCODERMOTORI2C_H
#define EASY_ENCODERMOTORI2C_H


#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\EncoderMotorBase.h"
#include "..\Kernel\MotorShieldAdafruitV2.h"

class EncoderMotorI2C : public EncoderMotorBase {
private:

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY
  EncoderMotorI2C(int aId, int aMotorNr, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed)
    : EncoderMotorBase(aId, CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_I2C_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed) {
    _motorShield = new MotorShieldAdafruitV2(aMotorNr);
  }
#endif

  //*************************************
  EncoderMotorI2C(int aMotorNr, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed)
    : EncoderMotorBase(CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_I2C_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed) {
    _motorShield = new MotorShieldAdafruitV2(aMotorNr);
  }
};

#endif