//*****************************************************************
//* Class VariablerInput - Implementation
//*
//* Represent an analog input pin. 
//* Define the pin A0...Ax into constructor. To raise not to many 
//* changes, the logic filter changes less than ConsideredMinChange. 
//* The constructor has an optional parameter to modify this value.
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

#include <Arduino.h>
#include "VariableInput.h"
#include "..\Common\Log.h"

#define IMPOSIBLE_VALUE_TO_INIT_VARIABLEINPUT 9999
#define VARIABLEINPUT_MINVALUE 0
#define VARIABLEINPUT_MAXVALUE 1023

//*************************************
#ifdef CREATE_ID_MANUALLY  
VariableInput::VariableInput(int aId, int aAnalogPin, int aConsideredMinChange) : Input(aId, CreateElementId(EbtInput, EkiAnalog, ANALOG_INPUT_INDEX), VARIABLEINPUT_MINVALUE, VARIABLEINPUT_MAXVALUE)
{
  Init(aAnalogPin, aConsideredMinChange);
}
#endif

//*************************************
VariableInput::VariableInput(int aAnalogPin, int aConsideredMinChange) : Input(CreateElementId(EbtInput, EkiAnalog, ANALOG_INPUT_INDEX), VARIABLEINPUT_MINVALUE, VARIABLEINPUT_MAXVALUE)
{
  Init(aAnalogPin, aConsideredMinChange);
}

//*************************************
void VariableInput::Init(int aAnalogPin, int aConsideredMinChange) 
{
#ifdef LOG_SETUP
  GetLog()->printf("VI(%d):C P=%d", _id, aAnalogPin );
#endif

  _analogPin = aAnalogPin;
  _consideredMinChange = aConsideredMinChange;
  _currentValue = _lastValue = IMPOSIBLE_VALUE_TO_INIT_VARIABLEINPUT;
}

//*************************************
void VariableInput::Loop()
{
  _currentValue = analogRead(_analogPin);
  if (abs(_currentValue - _lastValue) > _consideredMinChange)
  {
#ifdef LOG_LOOP
    GetLog()->printf("VI(%d):L Vl=%d", _id, _currentValue);
#endif
    _lastValue = _currentValue;
    _currentValue = _currentValue;
  }
  else
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("VI(%d):L ignore LVl=%d CVl=%d", _id, _lastValue, _currentValue);
#endif   
  }
}
