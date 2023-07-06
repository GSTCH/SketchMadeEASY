//*****************************************************************
//* Class FixValue - Header
//*
//* Represent a fix value input
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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

#ifndef FixValue_h
#define FixValue_h

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

#define FIXVALUE_HIGH 1
#define FIXVALUE_LOW 0
#define FIXVALUE_ON 1
#define FIXVALUE_OFF 0

class FixValue : public Input {
private:
  void init(int aConstant) {
#ifdef LOG_SETUP
    GetLog()->printf("FV(%d):C Vl=%d", _id, aConstant);
#endif

    _lastValue = aConstant;
    _currentValue = aConstant;
  }

public:
#ifdef CREATE_ID_MANUALLY	
  FixValue(int aId, int aConstant)
    : Input(aId, CreateElementId(EbtInput, EkiHelper, INHELPER_FIXVALUE_INDEX), aConstant, aConstant) {
    init(aConstant);
  }
  
  FixValue(int aId, int aConstant, int aMinValue, int aMaxValue)
    : Input(aId, CreateElementId(EbtInput, EkiHelper, INHELPER_FIXVALUE_INDEX), aMinValue, aMaxValue) {
    init(aConstant);
  }
#endif

  FixValue(int aConstant)
    : Input(CreateElementId(EbtInput, EkiHelper, INHELPER_FIXVALUE_INDEX), aConstant, aConstant) {
    init(aConstant);
  }
  
  FixValue(int aConstant, int aMinValue, int aMaxValue)
    : Input(CreateElementId(EbtInput, EkiHelper, INHELPER_FIXVALUE_INDEX), aMinValue, aMaxValue) {
    init(aConstant);
  }

  inline void SetValue(int aValue) {
#ifdef LOG_LOOP
    GetLog()->printf("FV(%d):S Vl=%d", _id, aValue);
#endif
    _lastValue = _currentValue;
    _currentValue = aValue;
  }

  static FixValue* High() {
    return new FixValue(FIXVALUE_HIGH, FIXVALUE_LOW, FIXVALUE_HIGH);
  }

  static FixValue* Low() {
    return new FixValue(FIXVALUE_LOW, FIXVALUE_LOW, FIXVALUE_HIGH);
  }

  static FixValue* On() {
    return new FixValue(FIXVALUE_ON, FIXVALUE_OFF, FIXVALUE_ON);
  }

  static FixValue* Off() {
    return new FixValue(FIXVALUE_OFF, FIXVALUE_OFF, FIXVALUE_ON);
  }

  static FixValue* Percent(int aValue) {
    return new FixValue(aValue, 0, 100);
  }
};
#endif
