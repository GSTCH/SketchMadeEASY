//*****************************************************************
//* Class ControlManagerFactory - Implementation
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

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "ControlManagerFactory.h"
#include "ControlManager.h"
#include <stdio.h>

ControlManagerBase* ControlManagerFactory::_ctrlMgr = NULL;

//************
//* Function GetControlManager()
//**********************
//* Use ControlManager with this Singleton pattern method.
//************
ControlManagerBase* ControlManagerFactory::GetControlManager() {
  if (_ctrlMgr == NULL) {
    _ctrlMgr = new ControlManager();
  }
  return _ctrlMgr;
}
