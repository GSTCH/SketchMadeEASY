//*****************************************************************
//* Class Switch3Position - Implementation
//*
//* Switch with three position. Use two diginal in pins
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

#include "Switch3Position.h"
#include "..\Common\Log.h"
#include <Arduino.h>

#define IMPOSIBLE_VALUE_TO_INIT_SWITCH3POSITION -1
#define PIN1INDEX 0
#define PIN2INDEX 1

//*************************************
#ifdef CREATE_ID_MANUALLY
Switch3Position::Switch3Position(int aId, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode)
  : Input(aId, CreateElementId(EbtInput, EkiDigital, DIGITAL_SWITCH3POSITION_INDEX), Switch3Position::Pos0, Switch3Position::Pos2) {
  Init(aPosition1Pin, aPosition2Pin, aSwitchResistoreMode, aDebounceTime);
}
#endif

//*************************************
Switch3Position::Switch3Position(int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime)
  : Input(CreateElementId(EbtInput, EkiDigital, DIGITAL_SWITCH3POSITION_INDEX), Switch3Position::Pos0, Switch3Position::Pos2) {
  Init(aPosition1Pin, aPosition2Pin, aSwitchResistoreMode, aDebounceTime);
}

//*************************************
void Switch3Position::Init(int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime) {
#ifdef LOG_SETUP
  GetLog()->printf("S3(%d):C P1=%d, P2=%d, M=%d", _id, aPosition1Pin, aPosition2Pin, aSwitchResistoreMode);
#endif

  _position1Pin = aPosition1Pin;
  _position2Pin = aPosition2Pin;
  _switchResistoreMode = aSwitchResistoreMode;
  _debounceTime = aDebounceTime;

  if (_switchResistoreMode == smPullUpExternal) {
    //PullUp, all initialized by LOW
    switchValue[Pos1][PIN1INDEX] = HIGH;
    switchValue[Pos2][PIN2INDEX] = HIGH;

    // Turn on position pins
    digitalWrite(_position1Pin, HIGH);
    digitalWrite(_position2Pin, HIGH);
  } else {
    switchValue[Pos0][PIN1INDEX] = HIGH;
    switchValue[Pos0][PIN2INDEX] = HIGH;
    switchValue[Pos1][PIN2INDEX] = HIGH;
    switchValue[Pos2][PIN1INDEX] = HIGH;
  }

  _lastValue = IMPOSIBLE_VALUE_TO_INIT_SWITCH3POSITION;
  _ignoreChangeMillis = millis();
}

//*************************************
void Switch3Position::Setup() {
  if (_switchResistoreMode == smPullDownInternal) {
    // Set internal PullUp mode to the pins
    pinMode(_position1Pin, INPUT_PULLUP);
    pinMode(_position2Pin, INPUT_PULLUP);

    // turn on pullup resistors
    digitalWrite(_position1Pin, HIGH);
    digitalWrite(_position2Pin, HIGH);
  } else {
    // Set external mode to the pins
    pinMode(_position1Pin, INPUT);
    pinMode(_position2Pin, INPUT);
  }
}

//*************************************
void Switch3Position::Loop() {
  unsigned long currentTime = millis();
  if (_ignoreChangeMillis > currentTime) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("S3(%d):L debounce", _id);
#endif
    return;
  }

  int valuePosition1 = digitalRead(_position1Pin);
  int valuePosition2 = digitalRead(_position2Pin);
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("S3(%d):L P1=%d, P2=%d", _id, valuePosition1, valuePosition2);
#endif

  if (valuePosition1 == switchValue[Pos1][PIN1INDEX] && valuePosition2 == switchValue[Pos1][PIN2INDEX]) {
    _currentValue = Switch3Position::Pos1;
    if (_lastValue != _currentValue) {
#ifdef LOG_LOOP
      GetLog()->printf("S3(%d):L CVl=1", _id);
#endif
      _ignoreChangeMillis = currentTime + _debounceTime;
    }
  } else if (valuePosition1 == switchValue[Pos2][PIN1INDEX] && valuePosition2 == switchValue[Pos2][PIN2INDEX]) {
    _currentValue = Switch3Position::Pos2;
    if (_lastValue != _currentValue) {
#ifdef LOG_LOOP
      GetLog()->printf("S3(%d):L CVl=2", _id);
#endif
      _ignoreChangeMillis = currentTime + _debounceTime;
    }
  } else if (valuePosition1 == switchValue[Pos0][PIN1INDEX] && valuePosition2 == switchValue[Pos0][PIN2INDEX]) {
    _currentValue = Switch3Position::Off;
    if (_lastValue != _currentValue) {
#ifdef LOG_LOOP
      GetLog()->printf("S3(%d):L CVl=0", _id);
#endif
      _ignoreChangeMillis = currentTime + _debounceTime;
    }
  } else {
    // both HIGH/LOW
#ifdef LOG_LOOP
    GetLog()->printf("S3(%d):L invalid", _id);
#endif
  }

  _lastValue = _currentValue;
}
