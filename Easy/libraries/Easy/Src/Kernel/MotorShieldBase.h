//*****************************************************************
//* Class MotorShieldBase - Header
//*
//* Internal base class for all motor shields
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

#ifndef EASY_MOTORSHIELDBASE_H
#define EASY_MOTORSHIELDBASE_H

#include "..\Common\BuildDefinition.h" // has to be the first 


class MotorShieldBase {
private:

protected:
  int _minMotorShieldSpeed = 0;
  int _maxMotorShieldSpeed = 255;

public:
  MotorShieldBase() {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("MS:C");
#endif
  }
  virtual void Setup() {}
  virtual void Loop() {}

  virtual void forward(int aSpeed) {}
  virtual void backward(int aSpeed) {}
  virtual void stop() {}

  inline int GetMinSpeed() {
    return _minMotorShieldSpeed;
  }

  inline int GetMaxSpeed() {
    return _maxMotorShieldSpeed;
  }
};
#endif