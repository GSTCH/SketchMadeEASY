//*****************************************************************
//* Class EncoderMotorL9110 - Header
//*
//* EncoderMotor controlled by an L9110h chip
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

#ifndef EASY_ENCODERMTORL9110_H
#define EASY_ENCODERMTORL9110_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\EncoderMotorBase.h"
#include "..\Kernel\MotorShieldL9110.h"

class EncoderMotorL9110 : public EncoderMotorBase {
private:
protected:
public:
  //*************************************
#ifdef CREATE_ID_MANUALLY
  EncoderMotorL9110(int aId, int aPinA, int aPinB, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed)
    : EncoderMotorBase(aId, CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L9110_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed) {
    _motorShield = new MotorShieldL9110(aPinA, aPinB);
  }
  
  EncoderMotorL9110(int aId, int aPinA, int aPinB, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed, float aKP, float aKI, float aKD)
    : EncoderMotorBase(aId, CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L9110_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed, aKP, aKI, aKD) {
    _motorShield = new MotorShieldL9110(aPinA, aPinB);
  }  
#endif

  EncoderMotorL9110(int aPinA, int aPinB, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed)
    : EncoderMotorBase(CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L9110_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed) {
    _motorShield = new MotorShieldL9110(aPinA, aPinB);
  }
 
  EncoderMotorL9110(int aPinA, int aPinB, int aSensorAPin, int aSensorBPin, int aPPR, int aGearRatio, int aMaxSpeed, float aKP, float aKI, float aKD)
    : EncoderMotorBase(CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L9110_INDEX), aSensorAPin, aSensorBPin, aPPR, aGearRatio, aMaxSpeed, aKP, aKI, aKD) {
    _motorShield = new MotorShieldL9110(aPinA, aPinB);
  }  
};

#endif