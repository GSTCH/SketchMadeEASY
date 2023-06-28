//*****************************************************************
//* Class MotorShieldStepperRotate - Header
//*
//* Internal class to set command of a stepper with controled rotation
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

#ifndef EASY_MOTORSHIELDSTEPPERROTATE_H
#define EASY_MOTORSHIELDSTEPPERROTATE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include <Arduino.h>
#include <AccelStepper.h>  // https://www.airspayce.com/mikem/arduino/AccelStepper/

class MotorShieldStepperRotate : public MotorShieldBase {
private:
  int _resolution;
  int _maxCylcesPerSecond;
  AccelStepper* _stepper;
  

  //*************************************
  void Init(int aPin1, int aPin2, int aPin3, int aPin4,
            int aResolution,  // Resolution of the stepper motor in "steps per one rotation"
            int aMaxCylcesPerSecond,
            EMotorInterfaceType aMotorInterfaceType) {
    _resolution = aResolution;
    _maxCylcesPerSecond = aMaxCylcesPerSecond;
    _minMotorShieldSpeed = 0;
    _maxMotorShieldSpeed = round(60.0 / aResolution * aMaxCylcesPerSecond);

    _stepper = new AccelStepper(aMotorInterfaceType, aPin1, aPin2, aPin3, aPin4, false);
  }

public:
  //*************************************
  MotorShieldStepperRotate(int aPin1, int aPin2, int aPin3, int aPin4, int aResolution, EMotorInterfaceType aMotorInterfaceType)
    : MotorShieldBase() {
#ifdef LOG_SETUP
      GetLog()->printf("SPS:C P1=%d, P2=%d, P3=%d, P4=%d, R=%d, I=%d", aPin1, aPin2, aPin3, aPin4, aResolution, aMotorInterfaceType);
#endif
    Init(aPin1, aPin2, aPin3, aPin4, 1000, aResolution, aMotorInterfaceType);   
  }

  //*************************************
  MotorShieldStepperRotate(int aPin1, int aPin2, int aPin3, int aPin4, int aResolution, int aMaxCylcesPerSecond, EMotorInterfaceType aMotorInterfaceType)
    : MotorShieldBase() {
#ifdef LOG_SETUP
      GetLog()->printf("SPS:C P1=%d, P2=%d, P3=%d, P4=%d, R=%d, I=%d, M=%d", aPin1, aPin2, aPin3, aPin4, aResolution, aMotorInterfaceType, _maxCylcesPerSecond);
#endif
    Init(aPin1, aPin2, aPin3, aPin4, aMaxCylcesPerSecond, aResolution, aMotorInterfaceType);
  }

  //*************************************
  void Setup() {
    _stepper->setMaxSpeed(_maxCylcesPerSecond);  // steps/sec
    _stepper->setAcceleration(500);
    _stepper->enableOutputs();
  }

  //*************************************
  void Loop() {
    _stepper->runSpeed();
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void forward(int aSpeed) {
    _stepper->setSpeed(round(aSpeed / 60.0 * _resolution));
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void backward(int aSpeed) {
    _stepper->setSpeed(-round(aSpeed / 60.0 * _resolution));
  }

  //*************************************
  void stop() {
    _stepper->stop();
  }
};

#endif