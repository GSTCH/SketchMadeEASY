//*****************************************************************
//* Class ServoBase - Implementation
//*
//* Servo logic base class
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

#include "ServoBase.h"  // has to be the first
#include "..\Common\Log.h"

//*************************************
 #ifdef CREATE_ID_MANUALLY  
ServoBase::ServoBase(int aId, int aMinAngle, int aMaxAngle, struct SElementType aElementType)
  : Actuator(aId, aElementType) {
#ifdef LOG_SETUP
  GetLog()->printf("SV(%d):C Min=%d, Max=%d", _id, aMinAngle, aMaxAngle);
#endif
  _minAngle = aMinAngle;
  _maxAngle = aMaxAngle;
}
 #endif

//*************************************
ServoBase::ServoBase(int aMinAngle, int aMaxAngle, struct SElementType aElementType)
  : Actuator(aElementType) {
#ifdef LOG_SETUP
  GetLog()->printf("SV(%d):C Min=%d, Max=%d", _id, aMinAngle, aMaxAngle);
#endif

  _minAngle = aMinAngle;
  _maxAngle = aMaxAngle;
}

//*************************************
void ServoBase::Setup() {
  _servoShield->Setup();
}

//*************************************
void ServoBase::Loop() {
  _servoShield->Loop();
}

//*************************************
void ServoBase::Act(Input* aInput) {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("SV(%d):A Vl=%d", _id, aInput->Value());
#endif

  int angleValue = round(aInput->Map(_minAngle, _maxAngle));
  if (_currentAngle != angleValue) {
#ifdef LOG_LOOP
    GetLog()->printf("SV(%d):A NVl=%d", _id, angleValue);
#endif
    angle(angleValue);
    _currentAngle = angleValue;  
  }
}

//*************************************
void ServoBase::angle(int aAngle) {
  _servoShield->angle(aAngle);
}
