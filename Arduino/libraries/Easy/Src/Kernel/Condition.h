//*****************************************************************
//* Class Condition - Header
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

#ifndef EASY_CONDITION_H
#define EASY_CONDITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "Input.h"
#include "Element.h"
#include "ControlManagerFactory.h"

enum ECompareOperator {
  OpEQ = 1,
  OpGT = 2,
  OpLT = 3,
  OpNEQ = 4,
  OpGTE = 5,
  OpLTE = 6,
};

class Condition : public Element {
private:
  //*************************************
  void init() {
    _lastCheck = false;
    _currentCheck = false;

    ControlManagerFactory::GetControlManager()->Add(this);
  }

protected:
  bool _lastCheck;
  bool _currentCheck;

  //*************************************
  bool CheckCondition(ECompareOperator aOperator, int aCompareParameter, int aCurrentValue) {
    switch (aOperator) {
      case OpEQ:
        return aCurrentValue == aCompareParameter;
      case OpGT:
        return aCurrentValue > aCompareParameter;
      case OpLT:
        return aCurrentValue < aCompareParameter;
      case OpNEQ:
        return aCurrentValue != aCompareParameter;
      case OpGTE:
        return aCurrentValue >= aCompareParameter;
      case OpLTE:
        return aCurrentValue <= aCompareParameter;
    }
    return false;
  }

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY  
  Condition(int aId, struct SElementType aElementType)
    : Element(aId, aElementType) {
    init();
  }
#endif  
  
  //*************************************
  Condition(struct SElementType aElementType)
    : Element(aElementType) {
    init();
  }

  //*************************************
  virtual bool Check() {
    return _currentCheck;
  }

  //*************************************
  bool CheckChanged() {
    return _lastCheck != _currentCheck;
  }
};
#endif
