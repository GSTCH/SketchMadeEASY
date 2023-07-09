//*****************************************************************
//* Class Encoder - Header
//*
//* Logic to motor with encoder to set an accurate RPM.
//* Motorshield are hidden by the base class MotorShieldBase,
//* with this class motor control by L9110, L298 and Adafruit 
//* MotorShield V2 are supported.
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

#ifndef EASY_ENCODERMOTORBASE_H
#define EASY_ENCODERMOTORBASE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "Actuator.h"
#include "MotorShieldBase.h"
#include "RotaryEncoder.h"

class EncoderMotorBase : public Actuator {
private:
  int _targetRpm = 0;
  int _maxRpm;
  ETurnDirection _targetDirection = moStop;
  // To calc the changes since the last loop, this member save the data of last loop.
  float _eintegral = 0;
  float _kp = 10.0;
  float _kd = 0.00;
  float _ki = 50.0;

protected:
  MotorShieldBase* _motorShield;
  RotaryEncoder* _rotaryEncoder;

public:
#ifdef CREATE_ID_MANUALLY 	
  EncoderMotorBase(int aId, struct SElementType aElementType, int aSensorAPin, int aSensorBPin, int aPPR, float aGearRatio, int aMaxRpm);
#endif  
  EncoderMotorBase(struct SElementType aElementType, int aSensorAPin, int aSensorBPin, int aPPR, float aGearRatio, int aMaxRpm);
  
  EncoderMotorBase(struct SElementType aElementType, int aSensorAPin, int aSensorBPin, int aPPR, float aGearRatio, int aMaxRpm, float aKP, float aKI, float aKD);
  
  void Setup();
  void Loop();
  void Act(Input* aInput);
};

#endif