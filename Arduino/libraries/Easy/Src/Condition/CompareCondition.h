//*****************************************************************
//* Class CompareCondition - Header
//*
//* Condition: Compare input with a value
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

#ifndef EASY_COMPARECONDITION_H
#define EASY_COMPARECONDITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"
#include "..\Kernel\Condition.h"

class CompareCondition : public Condition {
private:
  //*************************************
  void init(Input* aInput, ECompareOperator aCompareOperator, int aCompareParameter) {
    _input = aInput;
    _compareOperator = aCompareOperator;
    _compareParameter = aCompareParameter;

#ifdef LOG_SETUP
    GetLog()->printf("CC(%d):C Op=%d, Vl=%d, IN(%d)", _id, aCompareOperator, aCompareParameter, aInput->GetId());
#endif
  }

protected:
  Input* _input;
  ECompareOperator _compareOperator;
  int _compareParameter;

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY	  
  CompareCondition(int aId, Input* aInput, ECompareOperator aCompareOperator, int aCompareParameter)
    : Condition(aId, CreateElementId(EbtCondition, EkcCompare, CONDITION_COMPARE_INDEX)) {
    init(aInput, aCompareOperator, aCompareParameter);
  }
#endif

  //*************************************
  CompareCondition(Input* aInput, ECompareOperator aCompareOperator, int aCompareParameter)
    : Condition(CreateElementId(EbtCondition, EkcCompare, CONDITION_COMPARE_INDEX)) {
    init(aInput, aCompareOperator, aCompareParameter);
  }

  //*************************************
  void Loop() {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("CC(%d):L", _id);
#endif

    _lastCheck = _currentCheck;

    _currentCheck = CheckCondition(_compareOperator, _compareParameter, _input->Value());

    if (_currentCheck) {
#ifdef LOG_LOOP
      if (CheckChanged()) {
        GetLog()->printf("CC(%d):L Ck=%d", _id, _currentCheck);        
      }
#endif
      return;
    }

    _currentCheck = false;
#ifdef LOG_LOOP_DEBUG
    if (CheckChanged()) {
      GetLog()->printf("CC(%d):L Ck=%d", _id, _currentCheck);
    }
#endif
  }
};
#endif
