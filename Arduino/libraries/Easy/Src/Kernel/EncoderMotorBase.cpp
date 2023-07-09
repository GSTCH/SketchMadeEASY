//*****************************************************************
//* Class Encoder - Implementation
//*
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

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "EncoderMotorBase.h"
#include <arduino.h>
#include <Math.h>

//*************************************
#ifdef CREATE_ID_MANUALLY 
EncoderMotorBase::EncoderMotorBase(int aId, struct SElementType aElementType, int aSensorAPin, int aSensorBPin, int aPPR, float aGearRatio, int aMaxRpm)
  : Actuator(aId, aElementType) {
  _maxRpm = aMaxRpm;
#ifdef LOG_SETUP
  GetLog()->printf("EM(%d):C1 PA=%d, PB=%d, PPR=%d, GR=%d, MaxRPM=%d", _id, aSensorAPin, aSensorBPin, aPPR, (int)aGearRatio, _maxRpm);
#endif
  _rotaryEncoder = new CRotaryEncoder(aSensorAPin, aSensorBPin, aGearRatio * aPPR);
}
#endif

//*************************************
EncoderMotorBase::EncoderMotorBase(struct SElementType aElementType, int aSensorAPin, int aSensorBPin, int aPPR, float aGearRatio, int aMaxRpm)
  : Actuator(aElementType) {
  _maxRpm = aMaxRpm;
#ifdef LOG_SETUP
  GetLog()->printf("EM(%d):C2 PA=%d, PB=%d, PPR=%d, GR=%d, MaxRpm=%d", _id, aSensorAPin, aSensorBPin, aPPR, (int)aGearRatio, _maxRpm);
#endif
  _rotaryEncoder = new RotaryEncoder(aSensorAPin, aSensorBPin, aGearRatio * aPPR);
}

//*************************************
EncoderMotorBase::EncoderMotorBase(struct SElementType aElementType, int aSensorAPin, int aSensorBPin, int aPPR, float aGearRatio, int aMaxRpm, float aKP, float aKI, float aKD)
  : Actuator(aElementType) {

  _kp = aKP;
  _ki = aKI;
  _kd = aKD;
  _maxRpm = aMaxRpm;
#ifdef LOG_SETUP
  GetLog()->printf("EM(%d):C3 PA=%d, PB=%d, PPR=%d, GR=%d, MxRPM=%d, KP=%f, KI=%f, KD=%f", _id, aSensorAPin, aSensorBPin, aPPR, (int)aGearRatio, _maxRpm, (int)aKP, (int)aKI, (int)aKD);
#endif
  _rotaryEncoder = new RotaryEncoder(aSensorAPin, aSensorBPin, aGearRatio * aPPR);
}

//*************************************
void EncoderMotorBase::Setup() {
  _motorShield->Setup();
  _rotaryEncoder->Setup();
}

//*************************************
//* Loop is a PID to control current target speed
void EncoderMotorBase::Loop() {
  _rotaryEncoder->Loop();

  if (_targetDirection == moStop) {
    // Motor has to stop
    return;
  }

  float deltaT = _rotaryEncoder->DurationSinceLastLoop;
  float speed = _rotaryEncoder->FilteredRotationalSpeed;

  // Compute the control signal speed
  float difference = (_targetRpm - speed);
  _eintegral += (difference * deltaT);
  float diverential = 0;
  if (_kd > 0 && deltaT > 0) {
    diverential = difference / deltaT;
  }

  float controlspeed = _kp * difference + _ki * _eintegral - _kd * diverential;
  int currentSpeed = (int)min(fabs(controlspeed), 255);
  if (currentSpeed > 255) {
    currentSpeed = 255;
  }

#ifdef PLOT_ENCODERMOTOR
  GetLog()->printf("T:%d, REr:%d, REf:%d, CS:%d, P:%d, I:%d, D:%d", (int)_targetRpm, (int)_rotaryEncoder->RotationalSpeed, (int)_rotaryEncoder->FilteredRotationalSpeed, (int)controlspeed, (int)difference, (int)_eintegral, (int)diverential);
#endif

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("EM(%d):L TS=%d, CS=(int)%d, RSf=%d, RSr=%d, P:%d, I:%d, D:%d", _id, _targetRpm, controlspeed, (int)_rotaryEncoder->FilteredRotationalSpeed, (int)_rotaryEncoder->RotationalSpeed, (int)difference, (int)_eintegral, (int)diverential);
#endif

  // Set the motor speed and direction
  if (controlspeed < 0) {
    _motorShield->backward(currentSpeed);
  } else if (controlspeed > 0) {
    _motorShield->forward(currentSpeed);
  }
}

//*************************************
//* Set current target speed
void EncoderMotorBase::Act(Input* aInput) {
  ETurnDirection direction = moStop;
  int newSpeed = 0;
  if (aInput->Value() != 0) {
    direction = aInput->Value() > 0 ? moForward : moBackward;
    newSpeed = _maxRpm != 0 ? aInput->Map(-_maxRpm, _maxRpm) : aInput->Value();
  }

  if (_targetRpm == newSpeed && _targetDirection == direction) {
    // Nothing changes
    return;
  }

#ifdef LOG_LOOP
  GetLog()->printf("EM(%d):A n=%d, Dir=%d", _id, newSpeed, direction);
#endif

  _targetRpm = newSpeed;
  _targetDirection = direction;

  if (_targetDirection == moStop) {
    // Nothing to do because motor stopped
    _motorShield->stop();
    _targetRpm = 0;
    _eintegral = 0;
  }
}