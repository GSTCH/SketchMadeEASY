//*****************************************************************
//* Class MotorShieldStepperRotate - Header
//*
//* Internal class to set command of a stepper with controled rotation
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

#ifndef EASY_MOTORSHIELDSTEPPERROTATE_H
#define EASY_MOTORSHIELDSTEPPERROTATE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include <Arduino.h>
#include <AccelStepper.h>  // https://www.airspayce.com/mikem/arduino/AccelStepper/

#ifndef STEPPERROTATE_MAX_CYCLES_PER_SEC
// 1000 PPS/sec (according to manufacturer)
#define STEPPERROTATE_MAX_CYCLES_PER_SEC 1000
#endif

#ifndef STEPPERROTATE_ACCELERATION_MSEC 
#define STEPPERROTATE_ACCELERATION_MSEC 250
#endif

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
#ifdef LOG_SETUP
      GetLog()->printf("SPS:C P1=%d, P2=%d, P3=%d, P4=%d, R=%d, I=%d, MaxC=%d", aPin1, aPin2, aPin3, aPin4, aResolution, aMotorInterfaceType, aMaxCylcesPerSecond);
#endif
				
    _resolution = aResolution;
    _maxCylcesPerSecond = aMaxCylcesPerSecond;
    _minMotorShieldSpeed = 0;
    _minMotorShieldSpeed = 0;
    _maxMotorShieldSpeed = round(1.0 * aMaxCylcesPerSecond / aResolution * 60);
#ifdef LOG_SETUP
    GetLog()->printf("SRI:C Vmax=%d", _maxMotorShieldSpeed);
#endif	

    _stepper = new AccelStepper(aMotorInterfaceType, aPin1, aPin2, aPin3, aPin4, false);
  }

public:
  //*************************************
  MotorShieldStepperRotate(int aPin1, int aPin2, int aPin3, int aPin4, int aResolution, EMotorInterfaceType aMotorInterfaceType)
    : MotorShieldBase() {
    Init(aPin1, aPin2, aPin3, aPin4, aResolution, STEPPERROTATE_MAX_CYCLES_PER_SEC, aMotorInterfaceType);   
  }

  //*************************************
  MotorShieldStepperRotate(int aPin1, int aPin2, int aPin3, int aPin4, int aResolution, int aMaxCylcesPerSecond, EMotorInterfaceType aMotorInterfaceType)
    : MotorShieldBase() {
    Init(aPin1, aPin2, aPin3, aPin4, aResolution, aMaxCylcesPerSecond, aMotorInterfaceType);
  }

  //*************************************
  void Setup() {
    _stepper->setMaxSpeed(_maxCylcesPerSecond);  // steps/sec
    _stepper->setAcceleration(STEPPERROTATE_ACCELERATION_MSEC);
    _stepper->enableOutputs();
  }

  //*************************************
  void Loop() {
    _stepper->runSpeed();
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void forward(int aSpeed) {
    float val = _resolution / 60.0 * aSpeed;
#ifdef _LOG_LOOP_DEBUG
    GetLog()->printf("SPS:F Spd=%d, Vl=%d", aSpeed, (int)val);
#endif	  
    _stepper->setSpeed(val);
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void backward(int aSpeed) {
	float val = -_resolution / 60.0 * aSpeed;
#ifdef _LOG_LOOP_DEBUG
    GetLog()->printf("SPS:B Spd=%d, Vl=%d", aSpeed, (int)val);
#endif	  
    _stepper->setSpeed(val);
  }

  //*************************************
  void stop() {
#ifdef _LOG_LOOP_DEBUG
    GetLog()->println("SPS:S");
#endif	 	  
    _stepper->stop();
  }
};

#endif