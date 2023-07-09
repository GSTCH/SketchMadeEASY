//*****************************************************************
//* Class Inverter - Header
//*
//* Input - Tool class to invert the sign of an input
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

#ifndef EASY_INVERTER_H
#define EASY_INVERTER_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

class Inverter : public Input
{
  private:
    void Init(Input* aInput)
    {
      _input = aInput;
      _minValue = - _input->GetMinValue();
      _maxValue = - _input->GetMaxValue();
    }

  protected:
    Input* _input;

  public:
    //*************************************
 #ifdef CREATE_ID_MANUALLY	
    Inverter(int aId, Input* aInput) : Input(aId, CreateElementId(EbtInput, EkiHelper, INHELPER_INVERTER_INDEX), -aInput->GetMinValue(), -aInput->GetMaxValue())
    {
      Init(aInput);
    }
 #endif
 
    //*************************************
    Inverter(Input* aInput) : Input(CreateElementId(EbtInput, EkiHelper, INHELPER_INVERTER_INDEX), -aInput->GetMinValue(), -aInput->GetMaxValue())
    {
      Init(aInput);
    }

    //*************************************
    void Loop()
    {
      _currentValue =  - _input->Value();
      _lastValue = - _input->GetLastValue();
    }
};

#endif
