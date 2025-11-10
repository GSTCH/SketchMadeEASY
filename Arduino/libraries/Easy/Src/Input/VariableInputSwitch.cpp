//*****************************************************************
//* Class VariableInput - Header
//*
//* Represent a combination of an analog input pin and
//* switch with three position. Typical used to control a 
//* motor with direction (switch) and motor (poti)
//*
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2025 by Hans Rothenbuehler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************

#include "VariableInputSwitch.h"
#include "..\Common\Log.h"

#ifndef EASY_VARIABLEINPUT_CONSIDERED_MIN_CHANGE
#define EASY_VARIABLEINPUT_CONSIDERED_MIN_CHANGE 5
#endif

#ifndef VARIABLEINPUT_MAXVALUE
#define VARIABLEINPUT_MAXVALUE 1023
#endif

//*************************************
#ifdef CREATE_ID_MANUALLY  
VariableInputSwitch::VariableInputSwitch (int aId, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime, int aConsideredMinChange) 
  : Input(CreateElementId(EbtInput, EkiAnalog, ANALOG_VARIABLEINPUTSWITCH_INDEX), -VARIABLEINPUT_MAXVALUE, VARIABLEINPUT_MAXVALUE)
 {
   Init (aAnalogPin, aPosition1Pin, aPosition2Pin, aSwitchResistoreMode, aDebounceTime, aConsideredMinChange)
 }
#endif

//*************************************
VariableInputSwitch::VariableInputSwitch (int aAnalogPin, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime, int aConsideredMinChange)
  : Input(CreateElementId(EbtInput, EkiAnalog, ANALOG_VARIABLEINPUTSWITCH_INDEX), -VARIABLEINPUT_MAXVALUE, VARIABLEINPUT_MAXVALUE)
{
  Init (aAnalogPin, aPosition1Pin, aPosition2Pin, aSwitchResistoreMode, aDebounceTime, aConsideredMinChange);
}

//*************************************
VariableInputSwitch::VariableInputSwitch (int aAnalogPin, int aPosition1Pin, int aPosition2Pin)
  : Input(CreateElementId(EbtInput, EkiAnalog, ANALOG_VARIABLEINPUTSWITCH_INDEX), -VARIABLEINPUT_MAXVALUE, VARIABLEINPUT_MAXVALUE)
{
  Init (aAnalogPin, aPosition1Pin, aPosition2Pin, smPullDownInternal, EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC, EASY_VARIABLEINPUT_CONSIDERED_MIN_CHANGE);
}   
	
//*************************************
void VariableInputSwitch::Setup()
{
  // Done in the used classes 
#ifdef LOG_SETUP
  GetLog()->printf("VS(%d):S", _id );
#endif
}

//*************************************
void VariableInputSwitch::Loop()
{
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("VS(%d):L", _id );
#endif

  if (_variableInput->ValueChanged() || _switch3Pos->ValueChanged())
  {
    _lastValue = _currentValue;
    if (_switch3Pos->Value() == Switch3Position::Pos0)
    {
#ifdef LOG_LOOP
  GetLog()->printf("VS(%d):L stp", _id );
#endif
    _currentValue = 0;
    }
    else if (_switch3Pos->Value() == Switch3Position::Pos1)
    {
#ifdef LOG_LOOP
  GetLog()->printf("VS(%d):L fwd=%d", _id, _variableInput->Value() );
#endif
      _currentValue = _variableInput->Value();
    }
    else if (_switch3Pos->Value() == Switch3Position::Pos2)
    {
#ifdef LOG_LOOP
  GetLog()->printf("VS(%d):L rwd=-%d", _id, _variableInput->Value() );
#endif
      _currentValue = -1 * _variableInput->Value();
    }
  }
}
