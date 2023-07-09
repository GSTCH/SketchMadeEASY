//*****************************************************************
//* Class ToggleSwitch - Implementation
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

#include "ToggleSwitch.h"
#include <Arduino.h>


#define IMPOSIBLE_VALUE_TO_INIT_TOGGLESWITCH 999

//*************************************
 #ifdef CREATE_ID_MANUALLY  
ToggleSwitch::ToggleSwitch (int aId, int aPinDirection1, int aPinDirection2, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec) : Input(aId, CreateElementId(EbtInput, EkiDigital, DIGITAL_TOGGLESWITCH_INDEX), ToggleSwitch::Pos1, ToggleSwitch::Pos2)
{
  Init(aPinDirection1, aPinDirection2, aSwitchResistoreMode, aDebounceTimeMSec);
}
 #endif
 
//*************************************
ToggleSwitch::ToggleSwitch (int aPinDirection1, int aPinDirection2, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec) : Input(CreateElementId(EbtInput, EkiDigital, DIGITAL_TOGGLESWITCH_INDEX), ToggleSwitch::Pos1, ToggleSwitch::Pos2)
{
  Init(aPinDirection1, aPinDirection2, aSwitchResistoreMode, aDebounceTimeMSec);
}

//*************************************
void ToggleSwitch::Init(int aPinDirection1, int aPinDirection2, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec)
{
#ifdef LOG_SETUP
  GetLog()->printf("TS(%d):C AcId=%d P1=%d, P2=%d, T=%d", _id, aPinDirection1, aPinDirection2, aDebounceTimeMSec);
#endif
  _pinDirection1 = aPinDirection1;
  _pinDirection2 = aPinDirection2;

  _lastValue = IMPOSIBLE_VALUE_TO_INIT_TOGGLESWITCH;  
  _currentValue = IMPOSIBLE_VALUE_TO_INIT_TOGGLESWITCH;  
  _debounceTimeMSec=aDebounceTimeMSec;
  _ignoreChangeMillis = 0;
  _switchResistoreMode = aSwitchResistoreMode;
  
  if (_switchResistoreMode == smPullUpExternal) {
    //PullUp - Switch pressed sets pin to high
    _switchPressed = HIGH;
  }
  else
  {
	  // PullDown - Swich not pressed is high.
	_switchNotPressed = HIGH;
  }
}

//*************************************
void ToggleSwitch::Setup()
{
  if (_switchResistoreMode == smPullDownInternal) {
    // Set internal PullUp mode to the pins
    pinMode(_pinDirection1, INPUT_PULLUP);
    pinMode(_pinDirection2, INPUT_PULLUP);

    // turn on pullup resistors
    digitalWrite(_pinDirection1, HIGH);
	digitalWrite(_pinDirection2, HIGH);
  } else {
    // Set external mode to the pins
    pinMode(_pinDirection1, INPUT);
	pinMode(_pinDirection2, INPUT);
  }
}

//*************************************
void ToggleSwitch::Loop()
{
  unsigned long currentTime = millis();
  if (_ignoreChangeMillis > currentTime)
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("TS(%d):L debounce", _id);
#endif
    return;
  }

  int valueDirection1 = digitalRead(_pinDirection1);
  int valueDirection2 = digitalRead(_pinDirection2);
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("TS(%d):L P1=%d, P2=%d ,Last=%d", _id,  valueDirection1, valueDirection2, _lastValue);
#endif
  
  _lastValue = _currentValue;

  if (valueDirection1 == _switchPressed && valueDirection2 == _switchNotPressed && _lastValue == ToggleSwitch::Pos1)
  {
    _currentValue = ToggleSwitch::Pos2;
    if (_lastValue != _currentValue)
    {
#ifdef LOG_LOOP
      GetLog()->printf("TS(%d):L LVl=1, CVl=%d", _id, ToggleSwitch::Pos2 );
#endif
      _ignoreChangeMillis = currentTime + _debounceTimeMSec;
    }
  }
  else if (valueDirection1 == _switchNotPressed && valueDirection2 == _switchPressed && _lastValue == ToggleSwitch::Pos2)
  {
    _currentValue = ToggleSwitch::Pos1;
    if (_lastValue != _currentValue)
    {
#ifdef LOG_LOOP
      GetLog()->printf("TS(%d):L LVl=2, CVl=%d", _id, ToggleSwitch::Pos1 );
#endif
      _ignoreChangeMillis = currentTime + _debounceTimeMSec;
    }
  }
  else if (_lastValue == IMPOSIBLE_VALUE_TO_INIT_TOGGLESWITCH)
  {
    _currentValue = ToggleSwitch::Pos1;
    if (_lastValue != _currentValue)
    {
#ifdef LOG_LOOP
      GetLog()->printf("TS(%d):L LVl=999 NVl=%d", _id, ToggleSwitch::Pos1 );
#endif
      _ignoreChangeMillis = currentTime + _debounceTimeMSec;
    }
  }
#ifdef LOG_LOOP
  else 
  {
    // both HIGH 
    if (valueDirection1 == _switchPressed && valueDirection2 == _switchPressed && _switchResistoreMode == smPullUpExternal)
    {
      GetLog()->printf("TS(%d):L 2*H", _id );
    }
  }
#endif
}
