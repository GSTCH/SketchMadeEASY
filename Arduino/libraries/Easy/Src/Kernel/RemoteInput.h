//*****************************************************************
//* Class RemoteInput - Header
//*
//* Internal base class
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

#ifndef EASY_REMOTEINPUT_H
#define EASY_REMOTEINPUT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "Input.h"

class RemoteInput : public Input {
private:
  //*************************************
  void Init(int aMinValue, int aMaxValue) {
#ifdef LOG_SETUP
    GetLog()->printf("RI(%d):C Min=%d, Max=%d", _id, aMinValue, aMaxValue);
#endif
    if (aMinValue >= 0 && aMaxValue > 0) {
      _lastValue = _currentValue = aMinValue;
    } else if (aMinValue <= 0 && aMaxValue < 0) {
      _lastValue = _currentValue = aMaxValue;
    } else {
      _lastValue = _currentValue = 0;
    }
  }

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY  
  RemoteInput(int aId, struct SElementType aElementType, int aMinValue, int aMaxValue)
    : Input(aId, aElementType, aMinValue, aMaxValue) {
    Init(aMinValue, aMaxValue);
  }
#endif

  //*************************************
  RemoteInput(struct SElementType aElementType, int aMinValue, int aMaxValue)
    : Input(aElementType, aMinValue, aMaxValue) {
    Init(aMinValue, aMaxValue);
  }

  //*************************************
  void SetValue(int aValue) {
    _lastValue = _currentValue;

    if (aValue > _maxValue) {
      _currentValue = _maxValue;
    } else if (aValue < _minValue) {
      _currentValue = _minValue;
    } else {
      _currentValue = aValue;
    }
	
#ifdef LOG_LOOP
    if (_currentValue != _lastValue){
      GetLog()->printf("RI(%d):Sv CVl=%d LVl=%d", _id, _currentValue, _lastValue);
	}
#endif
  }

  //*************************************
  int SetMapValue(int aValue, int aMinRange, int aMaxRange) {
    _lastValue = _currentValue;
    _currentValue = map(aValue, aMinRange, aMaxRange, _minValue, _maxValue);

#ifdef LOG_LOOP_DEBUG
    if (_lastValue != _currentValue) {
      GetLog()->printf("RI(%d):Sv CVl=%d LVl=%d", _id, _currentValue, _lastValue);
    }
#endif
  }  
};
#endif