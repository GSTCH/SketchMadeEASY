//*****************************************************************
//* Class Input - Header
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

#ifndef EASY_INPUT_H
#define EASY_INPUT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "Element.h"
#include "ControlManagerFactory.h"
#include <arduino.h>

class Input : public Element {
private:
  //*************************************
  void Init(int aMinValue, int aMaxValue) {
#ifdef LOG_SETUP
    GetLog()->printf("IN(%d):C Min=%d, Max=%d", _id, aMinValue, aMaxValue);
#endif

    _minValue = aMinValue;
    _maxValue = aMaxValue;

    ControlManagerFactory::GetControlManager()->Add(this);
  }

protected:
  int _minValue;  // READONLY!
  int _maxValue;  // READONLY!
  int _lastValue;
  int _currentValue;

public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY  
  Input(int aId, struct SElementType aElementType, int aMinValue, int aMaxValue)
    : Element(aId, aElementType) {
    Init(aMinValue, aMaxValue);
  }
#endif

  //*************************************
  Input(struct SElementType aElementType, int aMinValue, int aMaxValue)
    : Element(aElementType) {
    Init(aMinValue, aMaxValue);
  }

  //*************************************
  virtual bool ValueChanged() {
    return _lastValue != _currentValue;
  }

  //*************************************
  int Map(int aMinValue, int aMaxValue) {
    if (_minValue != _maxValue) {
      int mappedValue = map(_currentValue, _minValue, _maxValue, aMinValue, aMaxValue);
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("In(%d):Mp In=%d Out=%d [%d..%d][%d %d]", _id, _currentValue, mappedValue, _minValue, _maxValue, aMinValue, aMaxValue);
#endif
      return mappedValue;
    }
    return _currentValue;
  }

  //*************************************
  inline int Value() {
    return _currentValue;
  }

  //*************************************
  inline int GetLastValue() {
    return _lastValue;
  }

  //*************************************
  inline int GetMinValue() {
    return _minValue;
  }

  //*************************************
  inline int GetMaxValue() {
    return _maxValue;
  }
  
  //*************************************
  inline void SetMinMaxValue(int aMinValue, int aMaxValue) {
    _minValue = aMinValue;
    _maxValue = aMaxValue;
  }
};
#endif
