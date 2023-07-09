//*****************************************************************
//* Class DigitalInput - Implementation
//*
//* Represent a digital input pin
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

#include "DigitalInput.h"
#include "..\Common\Log.h"
#include <Arduino.h>

#define IMPOSIBLE_VALUE_TO_INIT_DIGITALIN -1
#
//*************************************
#ifdef CREATE_ID_MANUALLY
DigitalInput::DigitalInput (int aId, int aPin, int aDebounceTime) : Input(aId, CreateElementId(EbtInput, EkiDigital, DIGITAL_INPUT_INDEX), DigitalInput::Off, DigitalInput::Pos1)
{
  Init(aPin, aDebounceTime);
}
#endif

//*************************************
DigitalInput::DigitalInput (int aPin, int aDebounceTime) : Input(CreateElementId(EbtInput, EkiDigital, DIGITAL_INPUT_INDEX), DigitalInput::Off, DigitalInput::Pos1)
{
  Init(aPin, aDebounceTime);
}

void DigitalInput::Init(int aPin, int aDebounceTime)
{
#ifdef LOG_SETUP
  GetLog()->printf("DI(%d):C P=%d", _id, aPin );
#endif

  _pin = aPin;
  _debounceTime = aDebounceTime; 
  _lastValue = IMPOSIBLE_VALUE_TO_INIT_DIGITALIN;
  _ignoreChangeMillis = millis();
}

//*************************************
void DigitalInput::Setup()
{
#ifdef LOG_SETUP
  GetLog()->printf("DI(%d):S", _id );
#endif

  pinMode(_pin, INPUT);
}

//*************************************
void DigitalInput::Loop()
{
  int pinValue = digitalRead(_pin);

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("DI(%d):L P=%d", _id,  pinValue);
#endif

  if (_ignoreChangeMillis > millis())
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("DI(%d):L debouncing", _id);
#endif
    return;
  }

  if (pinValue == HIGH)
  {
    _currentValue = DigitalInput::Pos1;
    if (_lastValue != _currentValue)
    {
#ifdef LOG_LOOP
      GetLog()->printf("DI(%d):L CVl=1", _id );
#endif
      _ignoreChangeMillis = millis() + _debounceTime;
    }
  }
  else // if (pinValue == LOW )
  {
    _currentValue = Off;
    if (_lastValue != _currentValue)
    {
#ifdef LOG_LOOP
      GetLog()->printf("DI(%d):L CVl=0", _id );
#endif
      _ignoreChangeMillis = millis() + _debounceTime;
    }
  }

  _lastValue = _currentValue;
}
