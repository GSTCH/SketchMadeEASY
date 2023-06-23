//*****************************************************************
//* Class ActionCollection - Header
//*
//*  Helper class when a relation should act multiple actions.
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

#ifndef EASY_ACTIONCOLLECTIONITEM_H
#define EASY_ACTIONCOLLECTIONITEM_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Action.h"
#include "..\Kernel\Input.h"

class ActionCollectionItem
{
    Action* _action = NULL;
    Input* _actionParameter = NULL;

  public:
    //*************************************
    ActionCollectionItem(Action* aAction, Input* aActionParameter)
    {
      _action  = aAction;
      _actionParameter = aActionParameter;
    }

    //*************************************
    void Setup()
    {
      _action->Setup();
    }

    //*************************************
    void Loop()
    {
      _action->Loop();
    }

    //*************************************
    void Act()
    {
      _action->Act(_actionParameter);
    }

    //*************************************
    bool ValueChanged()
    {
      if (_actionParameter != NULL)
      {
        return _actionParameter->ValueChanged();
      }
      return false;
    }
};

#endif
