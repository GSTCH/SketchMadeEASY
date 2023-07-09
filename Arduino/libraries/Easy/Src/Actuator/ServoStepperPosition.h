//*****************************************************************
//* Class ServoStepperPosition - Header
//*
//* Stepper motor control class use AccelStepper-Library.
//* Different chipls like L298n or L9110h are supported.
//* Details read https://www.airspayce.com/mikem/arduino/AccelStepper/
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

#ifndef EASY_SERVOSTEPPERPOSITION_H
#define EASY_SERVOSTEPPERPOSITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\ServoStepperPositionBase.h"
#include "..\Kernel\ServoShieldStepperPosition.h"

class ServoStepperPosition : public ServoStepperPositionBase {
private:
public:  
  //*************************************
  ServoStepperPosition(int aPin1, int aPin2, int aPin3, int aPin4, int aRotationSpeed, int aMinAngle, int aMaxAngle, int aResolution, EInitializeMode aInitializeMode = spNone, int aHomeSwitchPin = 0, EMotorInterfaceType aMotorInterfaceType = miFull4Wire)
    : ServoStepperPositionBase(aMinAngle, aMaxAngle, aResolution, aInitializeMode, aHomeSwitchPin) {
    _servoShield = new ServoShieldStepperPosition(aPin1, aPin2, aPin3, aPin4, aResolution, aRotationSpeed, aMotorInterfaceType);
    Init(aInitializeMode, aHomeSwitchPin, aResolution);
  }
};

#endif
