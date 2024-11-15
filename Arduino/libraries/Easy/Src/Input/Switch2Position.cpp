//*****************************************************************
//* Class Switch2Position - Implementation
//*
//* Switch with two position. Use one diginal input pins.
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#include "Switch2Position.h"
#include "..\Common\Log.h"
#include <Arduino.h>

#define IMPOSIBLE_VALUE_TO_INIT_SWITCH2POSITION -1


//*************************************
#ifdef CREATE_ID_MANUALLY 
Switch2Position::Switch2Position(int aId, int aPosition1Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime)
  : Input(aId, CreateElementId(EbtInput, EkiDigital, DIGITAL_SWITCH2POSITION_INDEX), Switch2Position::Pos0, Switch2Position::Pos1) {
  Init(aPosition1Pin, aSwitchResistoreMode, aDebounceTime);
}
#endif

//*************************************
Switch2Position::Switch2Position(int aPosition1Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime)
  : Input(CreateElementId(EbtInput, EkiDigital, DIGITAL_SWITCH2POSITION_INDEX), Switch2Position::Pos0, Switch2Position::Pos1) {
  Init(aPosition1Pin, aSwitchResistoreMode, aDebounceTime);
}

//*************************************
void Switch2Position::Init(int aPosition1Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime) {
#ifdef LOG_SETUP
  GetLog()->printf("S2(%d):C P1=%d, M=%d", _id, aPosition1Pin, aSwitchResistoreMode);
#endif

  _position1Pin = aPosition1Pin;
  _switchResistoreMode = aSwitchResistoreMode;
  _debounceTime = aDebounceTime;

#ifdef ARDUINO_ARCH_ESP32
  if (_switchResistoreMode == smPullUpExternal ||_switchResistoreMode ==smPullUpInternal) {
#else 
  if (_switchResistoreMode == smPullUpExternal ) {  
 #endif
    //PullUp
    switchValue[Pos0] = HIGH;
  } else {
    // PullDown
    switchValue[Pos1] = HIGH;
  }

  _lastValue = IMPOSIBLE_VALUE_TO_INIT_SWITCH2POSITION;
  _ignoreChangeMillis = millis();
}

//*************************************
void Switch2Position::Setup() {
  switch(_switchResistoreMode)
  {
    // Set mode to the pin
    case smPullDownInternal:
      pinMode(_position1Pin, INPUT_PULLUP);
      // turn on pullup resistors
      digitalWrite(_position1Pin, HIGH);
      break;
    case smPullDownExternal:
      pinMode(_position1Pin, INPUT);
      digitalWrite(_position1Pin, HIGH);
      break;
    case smPullUpExternal:
      pinMode(_position1Pin, INPUT);
      break;
#ifdef ARDUINO_ARCH_ESP32
    case smPullUpInternal:
      pinMode(_position1Pin, INPUT_PULLDOWN);
      break;
#endif    
  }
}

//*************************************
void Switch2Position::Loop() {
  unsigned long currentTime = millis();
  if (_ignoreChangeMillis > currentTime) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("S2(%d):L debounce", _id);
#endif
    return;
  }

  int valuePosition1 = digitalRead(_position1Pin);
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("S2(%d):L P1=%d", _id, valuePosition1);
#endif

  if (valuePosition1 == switchValue[Pos1]) {
	// Position1  
    _currentValue = Switch2Position::Pos1;
    if (_lastValue != _currentValue) {
#ifdef LOG_LOOP
      GetLog()->printf("S2(%d):L CVl=1", _id);
#endif
      _ignoreChangeMillis = currentTime + _debounceTime;
    }
  } else {
    // Position 0
    _currentValue = Switch2Position::Off;
    if (_lastValue != _currentValue) {
#ifdef LOG_LOOP
      GetLog()->printf("S2(%d):L CVl=0", _id);
#endif
      _ignoreChangeMillis = currentTime + _debounceTime;
    }
  }

  _lastValue = _currentValue;
}
