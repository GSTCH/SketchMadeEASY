//*****************************************************************
//* Class RemoteJoystickAxis - Header
//*
//* Virtual joystick axis. value defined extern by remote control
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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

#ifndef EASY_REMOTEJOYSTICKAXIS_H
#define EASY_REMOTEJOYSTICKAXIS_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\RemoteInput.h"

#define REMOTEJOYSTICKAXIS_MINVALUE -255
#define REMOTEJOYSTICKAXIS_MAXVALUE 255
#define DEATH_ZONE_WIDTH 10


class RemoteJoystickAxis : public RemoteInput
{
  private:
    void Init(bool aSwitchDirection)
    {
      _switchDirection = aSwitchDirection;
      _deathZoneWidth = DEATH_ZONE_WIDTH;
    }

  protected:
    bool _switchDirection;
    int _deathZoneWidth;

  public:  
    //*************************************
#ifdef CREATE_ID_MANUALLY 	
    RemoteJoystickAxis (int aId, bool aSwitchDirection) : RemoteInput(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_JOYSTICKAXIS_INDEX), REMOTEJOYSTICKAXIS_MINVALUE, REMOTEJOYSTICKAXIS_MAXVALUE)
    {
      Init(aSwitchDirection);
    }
#endif

    //*************************************
    RemoteJoystickAxis (bool aSwitchDirection) : RemoteInput(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_JOYSTICKAXIS_INDEX), REMOTEJOYSTICKAXIS_MINVALUE, REMOTEJOYSTICKAXIS_MAXVALUE)
    {
      Init(aSwitchDirection);
    }

    //*************************************
#ifdef CREATE_ID_MANUALLY 	
    RemoteJoystickAxis (int aId, int aMinValue, int aMaxValue, bool aSwitchDirection) : RemoteInput(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_JOYSTICKAXIS_INDEX), aMinValue, aMaxValue)
    {
      Init(aSwitchDirection);
    }
#endif

    //*************************************
    RemoteJoystickAxis (int aMinValue, int aMaxValue, bool aSwitchDirection) : RemoteInput(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_JOYSTICKAXIS_INDEX), aMinValue, aMaxValue)
    {
      Init(aSwitchDirection);
    }

    //*************************************
    void Loop()
    {	  
      RemoteInput::Loop();

      if (abs(_currentValue) < _deathZoneWidth)
      {
        SetValue(0);
      }

      if (_switchDirection)
      {
        SetValue(-_currentValue);
      }
    }
};
#endif
