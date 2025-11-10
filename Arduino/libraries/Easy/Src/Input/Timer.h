//*****************************************************************
//* Class Timer - Header
//*
//* Input - Tool class the value toggles between two values (0/1).
//* There are consts On/Off or High/Low do make sketches more readable.
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

#ifndef EASY_TIMER_H
#define EASY_TIMER_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

class Timer : public Input {
private:
  //*************************************
  void init(unsigned long aIntervalMSec, bool aStartHigh, int aTimes) {
#ifdef LOG_SETUP
    GetLog()->printf("TI(%d):C Intvl=%d, Start=%d, Times=%d", _id, aIntervalMSec, aStartHigh, aTimes);
#endif
    _intervalMSec = aIntervalMSec;
    if (aTimes <= 0) {
      _currentValue = _lastValue = aStartHigh ? 1 : 0;
      _times = -1;
    } else {
      if (aStartHigh) {
        _currentValue = _lastValue = 1;
        _times = aTimes * 2;
      } else {
        _currentValue = _lastValue = 0;
        _times = (aTimes - 1) / 2 * 4 + 1;
      }
    }
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("TI(%d):C T=%d, CVl=%d, LVl=%d", _id, _times, _currentValue, _lastValue);
#endif
  }

protected:
  unsigned long _intervalMSec;
  unsigned long _lastStateChangeMilli;
  int _times;

public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY    
  Timer(int aId, unsigned long aIntervalMSec, bool aStartHigh, int aTimes)
    : Input(aId, CreateElementId(EbtInput, EkiHelper, INHELPER_TIMER_INDEX), 0, !0) {
    init(aIntervalMSec, aStartHigh, aTimes);
  }
#endif

  //*************************************
  Timer(unsigned long aIntervalMSec, bool aStartHigh, int aTimes = -1)
    : Input(CreateElementId(EbtInput, EkiHelper, INHELPER_TIMER_INDEX), 0, !0) {
    init(aIntervalMSec, aStartHigh, aTimes);
  }

  //*************************************
  void Setup() {
#ifdef LOG_LOOP
    GetLog()->printf("TI(%d):S start %d", _id, _currentValue);
#endif
    _lastStateChangeMilli = millis();
    ;
  }

  //*************************************
  void Loop() {
    if (_times == 0) {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("TI(%d):L time finished", _id);
#endif
      return;
    }
    _lastValue = _currentValue;

    unsigned long currentTime = millis();

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("TI(%d):L CT=%u LT=%u", _id, currentTime, _lastStateChangeMilli);
#endif

    if (currentTime > (_lastStateChangeMilli + _intervalMSec)) {
      if (_times > 0) {
#ifdef LOG_LOOP
        GetLog()->printf("TI(%d):L times decrease Tm=%d Last=%d", _id, _times, _currentValue);
#endif
        _times--;
      }

      _lastStateChangeMilli = currentTime;
      _currentValue = !_currentValue;
    }
  }

  static const int High = 1;
  static const int Low = 0;

  static const int On = 1;
  static const int Off = 0;
};

#endif
