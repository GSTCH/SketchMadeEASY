//*****************************************************************
//* Class MotorBase - Header
//*
//* Internal base class for all motors. 
//* Motor are different in the kind of using the MotorShield and 
//* not into the logic to control the motor. This class is the 
//* logic part of motor control. It use a (base class) for the 
//* shield to set command to hardware. For this each kind of motor 
//* shield control has a derived motorshield class.
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

#ifndef EASY_MOTORBASE_H
#define EASY_MOTORBASE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "Actuator.h"
#include "MotorShieldBase.h"

class MotorBase : public Actuator {
private:
  int _currentSpeed;
  ETurnDirection _currentDirection;

  unsigned long _delayedMillis;
  int _delayedSpeed;
  ETurnDirection _delayedDirection;

  void init();
  void delayedStart(ETurnDirection aDirection, int aSpeed);

protected:
  MotorShieldBase* _motorShield;

public:
#ifdef CREATE_ID_MANUALLY 
  MotorBase(int aId, struct SElementType aElementType);
#endif  
  MotorBase(struct SElementType aElementType);

  void Setup();
  void Loop();
  void Act(Input* aInput);

  void forward(int aSpeed);
  void backward(int aSpeed);
  void stop();
  
  inline int getMinSpeed() {
    return _motorShield->GetMinSpeed();
  }

  inline int getMaxSpeed() {
    return _motorShield->GetMaxSpeed();
  }
};

#endif