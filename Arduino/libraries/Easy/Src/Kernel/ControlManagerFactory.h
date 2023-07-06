//*****************************************************************
//* Class ControlManagerFactory - Header
//*
//* Internal class
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

#ifndef EASY_CONTROLMANAGERFACTORY_H
#define EASY_CONTROLMANAGERFACTORY_H

#include "ControlManagerBase.h"

//**********************
//* Use ControlManager with this Singleton pattern method.
//* To prevent circular dependency, it works with a abstract base class.
//************
class ControlManagerFactory
{
  private:
    static ControlManagerBase* _ctrlMgr;

  public:
    static ControlManagerBase* GetControlManager();
};
#endif
