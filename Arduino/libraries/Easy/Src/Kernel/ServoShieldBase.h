//*****************************************************************
//* Class ServoShieldBase - Header
//*
//* Base class to implement hardware calls of the servo logic
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

#ifndef EASY_SERVOSHIELDBASE_H
#define EASY_SERVOSHIELDBASE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"

class ServoShieldBase
{
  private:

  protected:

  public:
    ServoShieldBase() {}
    virtual void Setup() {}
    virtual void Loop() {}
    virtual void angle(int aAngle) {}

    virtual void step(int aSteps) {} // Used in case of a stepper eg to initialize
    virtual void resetPosition() {}  // Used in case of a stepper eg to set 0 position
};
#endif
