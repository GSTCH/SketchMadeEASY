//*****************************************************************
//* Class Action - Header
//*
//* Internal base class
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

#ifndef EASY_ACTION_H
#define EASY_ACTION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "Element.h"
#include "Input.h"
#include "ControlManagerFactory.h"

class Input;

class Action : public Element
{
  protected:

  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY
    Action(int aId, struct SElementType aElementType) : Element(aId, aElementType)
    {
      ControlManagerFactory::GetControlManager()->Add(this);
    }
#endif

    //*************************************
    Action(struct SElementType aElementType) : Element(aElementType)
    {
      ControlManagerFactory::GetControlManager()->Add(this);
    }

    //*************************************
    virtual void Act(Input* aInput)
    {
    }
};

#endif
