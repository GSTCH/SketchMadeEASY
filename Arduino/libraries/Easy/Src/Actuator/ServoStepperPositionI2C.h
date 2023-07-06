//*****************************************************************
//* Class ServoStepperPositionI2C - Header
//*
//* For Adafruit motor shield V2 it use the library of adafruit with a separate constructor
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

#ifndef EASY_SERVOSTEPPERPOSITIONI2C_H
#define EASY_SERVOSTEPPERPOSITIONI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\ServoStepperPositionBase.h"
#include "..\Kernel\ServoShieldStepperPositionI2C.h"

class ServoStepperPositionI2C : public ServoStepperPositionBase {
private:
public:
  //*************************************
  //* Adafruit MotorShield V2:
  //* aStepperNr : Number of stepper on shield
  //* aResolution : steps per revolution of the stepper motor (without gear) [PPS]
  //* aGearRatio : Gear box ratio
  //* aRotationSpeed : Speed of the motor [rotations per minute]. 
  //* aStepStyle : Type of stepper motor signal (ssSingle, ssDouble, ssInterleave, ssMicrostep)
  //* aBusAdddress : I2C Address of the shield
  ServoStepperPositionI2C(int aStepperNr, int aResolution, int aGearRatio, int aMinAngle, int aMaxAngle, int aRotationSpeed = 50, EInitializeMode aInitializeMode = spNone, int aHomeSwitchPin = 0, EStepStyle aStepStyle = ssSingle, int aBusAdddress = 0x60)
    : ServoStepperPositionBase(aMinAngle, aMaxAngle, aResolution, aInitializeMode, aHomeSwitchPin) {
    _servoShield = new ServoShieldStepperPositionI2C(aStepperNr, aResolution, aRotationSpeed*aGearRatio, aStepStyle, aBusAdddress);
  }
};

#endif
