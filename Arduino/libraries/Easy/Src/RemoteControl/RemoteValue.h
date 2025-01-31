//*****************************************************************
//* Class RemoteJoystickAxis - Header
//*
//* Virtual input. value defined extern by remote control
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

#ifndef EASY_REMOTEVALUE_H
#define EASY_REMOTEVALUE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\RemoteInput.h"

#define REMOTEVALUE_MINVALUE 0
#define REMOTEVALUE_MAXVALUE 2

class RemoteValue : public RemoteInput
{
  private:

  protected:

  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY 	
    RemoteValue (int aId) : RemoteInput(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VALUE_INDEX), REMOTEVALUE_MINVALUE, REMOTEVALUE_MAXVALUE)
    {
    }
#endif

    //*************************************
    RemoteValue () : RemoteInput(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VALUE_INDEX), REMOTEVALUE_MINVALUE, REMOTEVALUE_MAXVALUE)
    {
    }

    //*************************************
#ifdef CREATE_ID_MANUALLY 	
    RemoteValue (int aId, int aMinValue, int aMaxValue) : RemoteInput(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VALUE_INDEX), aMinValue, aMaxValue)
    {
    }
#endif

    //*************************************
    RemoteValue (int aMinValue, int aMaxValue) : RemoteInput(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VALUE_INDEX), aMinValue, aMaxValue)
    {
    }

    //*************************************
RemoteValue (int aValue, int aMinValue, int aMaxValue) : RemoteInput(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VALUE_INDEX), aMinValue, aMaxValue)
    {
        _currentValue = aValue;
    }    

    //*************************************
    void Loop()
    {
      RemoteInput::Loop();
    }

    //*************************************
	  static const int Pos2 = 2;
    static const int Pos1 = 1;
    static const int Pos0 = 0;
};
#endif
