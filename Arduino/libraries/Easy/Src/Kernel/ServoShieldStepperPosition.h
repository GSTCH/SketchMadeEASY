//*****************************************************************
//* Class ServoShieldStepperPosition - Header
//*
//* Internal class to set command of a stepper with controled position
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

#ifndef EASY_SERVOSHIELDSTEPPERPOSITION_H
#define EASY_SERVOSHIELDSTEPPERPOSITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "ServoShieldBase.h"
#include <Arduino.h>
#include <AccelStepper.h>  // https://www.airspayce.com/mikem/arduino/AccelStepper/

#ifndef EASY_MAX_SPEED
#define EASY_MAX_SPEED 1500
#endif

#ifndef EASY_ACCELERATION
#define EASY_ACCELERATION 500
#endif


class ServoShieldStepperPosition : public ServoShieldBase {
private:
  float _degreePerStep;
  int _rotationSpeed;
  int _resolution;
  AccelStepper* _stepper;

public:
  //*************************************
  //* aResolution : steps per revolution (with gear multiple motor SPR with gear ratio)
  //* aRotationSpeed : [rotations per minute]
  //* aBusAdddress : I2C Address of the shield
  ServoShieldStepperPosition(
    int aPin1, int aPin2, int aPin3, int aPin4,
    int aResolution,     // Resolution of the stepper motor in "steps per one rotation"
    int aRotationSpeed,  // RPM
    EMotorInterfaceType aMotorInterfaceType) {
#ifdef LOG_SETUP
    GetLog()->printf("SPS:C P1=%d, P2=%d, P3=%d, P4=%d, R=%d, S=%d, I=%d", aPin1, aPin2, aPin3, aPin4, aResolution, aRotationSpeed, aMotorInterfaceType);
#endif
    if (aMotorInterfaceType == miHalf4Wire) {
      _resolution = aResolution * 2;
    } else {
      _resolution = aResolution;
    }
    _degreePerStep = 360.0 / aResolution;

    speed(aRotationSpeed);

    _stepper = new AccelStepper(aMotorInterfaceType, aPin1, aPin2, aPin3, aPin4, false);
  }

  //*************************************
  void Setup() {
    _stepper->enableOutputs();
    _stepper->setMaxSpeed(EASY_MAX_SPEED);         // steps/sec
    _stepper->setSpeed(_rotationSpeed);  // steps/sec
    _stepper->setAcceleration(EASY_ACCELERATION);
  }

  //*************************************
  void Loop() {
    if (_stepper->run()) {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("SPS:L CPs=%d Ds=%d", _stepper->currentPosition(), _stepper->distanceToGo());
#endif
    }
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void angle(int aAngle) {
    int steps = round(aAngle / _degreePerStep);
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SPS:agl A=%d S=%d", aAngle, steps);
#endif
    _stepper->moveTo(steps);
    _stepper->runToPosition();
  }

  //*************************************
  //* aRotationSpeed : [rotations per minute]
  void speed(int aRotationSpeed) {
    _rotationSpeed = round(aRotationSpeed / 60.0 * _resolution);
    _stepper->setSpeed(_rotationSpeed);  // steps/sec
  }

  //*************************************
  void step(int aSteps) {
    _stepper->move(aSteps);
    _stepper->runToPosition();
  }

  //*************************************
  void resetPosition() {
    _stepper->setCurrentPosition(0);
  }
};

#endif