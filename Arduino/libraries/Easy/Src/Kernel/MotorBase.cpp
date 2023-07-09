//*****************************************************************
//* Class MotorBase - Header
//*
//* Internal base class for all motors
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

#include "MotorBase.h"
#include "..\Common\Log.h"
#include <arduino.h>

#ifndef TIME_UNTIL_MOTOR_STOPED_MS
// Wait time when motor change direction without stop (mass inertia). Increase this time when moving large/heavy constructions.
#define TIME_UNTIL_MOTOR_STOPED_MS 500
#endif

//*************************************
#ifdef CREATE_ID_MANUALLY 
MotorBase::MotorBase(int aId, struct SElementType aElementType)
  : Actuator(aId, aElementType) {
  init();
}
#endif

//*************************************
MotorBase::MotorBase(struct SElementType aElementType)
  : Actuator(aElementType) {
  init();
}

//*************************************
void MotorBase::Setup() {
  _motorShield->Setup();
}

//*************************************
void MotorBase::Act(Input* aInput) {
  int mappedSpeed;
  if (aInput->GetMinValue() == 0 && aInput->GetMaxValue() != 0) {
	// Sign defines the rotation direction, the speed is from 0...MAX 
    if (aInput->Value() > 0)
	{
	  mappedSpeed = aInput->Map(0, abs(_motorShield->GetMaxSpeed()));
	}
	else if (aInput->Value() < 0)
	{
	  mappedSpeed = aInput->Map(0, -abs(_motorShield->GetMaxSpeed()));
	}	
	else
	{
	  mappedSpeed = 0;
	}	
  } else {	 
    // Input is from -MAX to +MAX, motor is from 0...MAX 
    mappedSpeed = abs(aInput->Map(-_motorShield->GetMaxSpeed(), _motorShield->GetMaxSpeed()));
  }

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("MO(%d):A Vl=%d MpVl=%d, I(%d)=(%d..%d), S=(%d..%d)", _id, aInput->Value(), mappedSpeed, aInput->GetId(), aInput->GetMinValue(), aInput->GetMaxValue(), _motorShield->GetMinSpeed(), _motorShield->GetMaxSpeed());
#endif

  if (aInput->Value() > 0) {
    forward(mappedSpeed);
  } else if (aInput->Value() < 0) {
    backward(mappedSpeed);
  } else {
    stop();
  }
}

//*************************************
void MotorBase::Loop() {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("MO(%d):L DT=%d", _id, _delayedMillis);
#endif

  if (_delayedMillis > 0) {
    unsigned long currentTime = millis();

    if (currentTime > _delayedMillis) {
#ifdef LOG_LOOP
      GetLog()->printf("MO(%d):L Delayed go Dr=%d, Sp=%d", _id, _delayedDirection, _delayedSpeed);
#endif

      _delayedMillis = 0;
      if (_delayedDirection == moForward) {
        forward(_delayedSpeed);
      } else if (_delayedDirection == moBackward) {
        backward(_delayedSpeed);
      }

      _delayedSpeed = 0;
      _delayedDirection = moStop;
    } else {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("MO(%d):L Delayed wait %lu < %lu", _id, _delayedMillis, currentTime);
#endif
    }
  } else {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):L No delay Dr=%d, Sp=%d", _id, _delayedDirection, _delayedSpeed);
#endif
  }

  _motorShield->Loop();
}

//*************************************
void MotorBase::init() {
#ifdef LOG_SETUP
  GetLog()->printf("MO(%d)::Init", _id);
#endif 
  _currentSpeed = 0;
  _currentDirection = moStop;

  _delayedMillis = 0;
  _delayedDirection = moStop;
  _delayedSpeed = 0;
}

//*************************************
void MotorBase::forward(int aSpeed) {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("MO(%d):Fd Sp=%d", _id, aSpeed);
#endif

  if (_currentSpeed == aSpeed && _currentDirection == moForward) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):Fd ignore", _id);
#endif
    return;
  }

  if (_currentDirection == moBackward && _delayedMillis == 0) {
    stop();

    // Physics: The model does not stops within one cycle. We have to make a non blocking wait.
    delayedStart(moForward, aSpeed);
    return;
  }

  if (_delayedMillis > 0) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):Fd delay %d", _id, _delayedMillis);
#endif

    _delayedDirection = moForward;
    _delayedSpeed = aSpeed;
    return;
  }

#ifdef LOG_LOOP
  GetLog()->printf("MO(%d):Fd Sp=%d", _id, aSpeed);
#endif

  // Hardware shield is implemented in derived class of CMotorShield.
  _motorShield->forward(aSpeed);

  _currentDirection = moForward;
  _currentSpeed = aSpeed;
}

//*************************************
void MotorBase::backward(int aSpeed) {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("MO(%d):Bk Sp=%d", _id, aSpeed);
#endif

  if (_currentSpeed == aSpeed && _currentDirection == moBackward) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):Bk ignore", _id);
#endif
    return;
  }

  if (_currentDirection == moForward && _delayedMillis == 0) {
    stop();
    // Physics: The model does not stops within one cycle. We have to make a non blocking wait.
    delayedStart(moBackward, aSpeed);
    return;
  }

  if (_delayedMillis > 0) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):Bk delay %d", _id, _delayedMillis);
#endif

    _delayedDirection = moBackward;
    _delayedSpeed = aSpeed;
    return;
  }

#ifdef LOG_LOOP
  GetLog()->printf("MO(%d):Bk Sp=%d", _id, aSpeed);
#endif

  // Hardware shield is implemented in derived class of CMotorShield.
  _motorShield->backward(aSpeed);

  _currentDirection = moBackward;
  _currentSpeed = aSpeed;
}

//*************************************
void MotorBase::stop() {
  if (_currentSpeed == 0 || _currentDirection == moStop) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):Sp Dr=%d, Sp=%d", _id, _currentDirection, _currentSpeed);
#endif
    return;
  }

#ifdef LOG_LOOP
  GetLog()->printf("MO(%d):Sp Dr=%d Sp=%d", _id, _currentDirection, _currentSpeed);
#endif

  // Hardware shield is implemented in derived class of CMotorShield.
  _motorShield->stop();

  _currentSpeed = 0;
  _currentDirection = moStop;

  if (_delayedMillis > 0) {
    // Stop a delayed start
    _delayedMillis = 0;
    _delayedDirection = moStop;
    _delayedSpeed = 0;
  }

  // Wait to start until motor has stopped
  unsigned long currentTime = millis();
  _delayedMillis = currentTime + TIME_UNTIL_MOTOR_STOPED_MS;
}

//*************************************
void MotorBase::delayedStart(ETurnDirection aDirection, int aSpeed) {
#ifdef LOG_LOOP
  GetLog()->printf("MO(%d):DS", _id);
#endif

  unsigned long currentTime = millis();
  _delayedDirection = aDirection;
  _delayedSpeed = aSpeed;

  if (_delayedMillis > 0) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MO(%d):DS CT=%lu", _id, currentTime);
#endif
  }
  _delayedMillis = currentTime + TIME_UNTIL_MOTOR_STOPED_MS;
}