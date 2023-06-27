//*****************************************************************
//* Class ActuatorCollection - Header
//*
//*  Helper class when a relation should act multiple Actuators.
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

#ifndef EASY_ACTUATORCOLLECTIONITEM_H
#define EASY_ACTUATORCOLLECTIONITEM_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Actuator.h"
#include "..\Kernel\Input.h"

class ActuatorCollectionItem
{
    Actuator* _Actuator = NULL;
    Input* _ActuatorParameter = NULL;

  public:
    //*************************************
    ActuatorCollectionItem(Actuator* aActuator, Input* aActuatorParameter)
    {
      _Actuator  = aActuator;
      _ActuatorParameter = aActuatorParameter;
    }

    //*************************************
    void Setup()
    {
      _Actuator->Setup();
    }

    //*************************************
    void Loop()
    {
      _Actuator->Loop();
    }

    //*************************************
    void Act()
    {
      _Actuator->Act(_ActuatorParameter);
    }

    //*************************************
    bool ValueChanged()
    {
      if (_ActuatorParameter != NULL)
      {
        return _ActuatorParameter->ValueChanged();
      }
      return false;
    }
};

#endif
