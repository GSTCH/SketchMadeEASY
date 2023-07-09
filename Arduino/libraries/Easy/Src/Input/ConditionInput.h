//*****************************************************************
//* Class ConditionInput - Header
//*
//* Input combined with a condition. Depending on whether the condition 
//* is met or not, a different input is used.
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

#ifndef EASY_CONDITIONINPUT_H
#define EASY_CONDITIONINPUT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"
#include "..\Kernel\Condition.h"

class ConditionInput : public Input {
private:
  bool _valueChanged;

  //*************************************
  void Init(Condition* aCondition, Input* aTrueInput, Input* aFalseInput) {
#ifdef LOG_SETUP
    if (aCondition == NULL || aTrueInput == NULL || aFalseInput == NULL) {
      GetLog()->println("CI(%d):C NULL!");
    }
#endif

#ifdef LOG_SETUP
    GetLog()->printf("CI(%d):C CD(%d), T(%d), F(%d)", _id, aCondition->GetId(), aTrueInput->GetId(), aFalseInput->GetId());
#endif
    _valueChanged = true;

    _condition = aCondition;
    _trueInput = aTrueInput;
    _falseInput = aFalseInput;

    _currentValue = _falseInput->Value();
    _lastValue = _falseInput->Value();
    _minValue = _falseInput->GetMinValue();
    _maxValue = _falseInput->GetMaxValue();
  }

protected:
  Condition* _condition;
  Input* _trueInput;
  Input* _falseInput;

  //*************************************
  virtual bool ValueChanged() {
    return _valueChanged;
  }

public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY	  
  ConditionInput(int aId, Condition* aCondition, Input* aTrueInput, Input* aFalseInput)
    : Input(aId, CreateElementId(EbtInput, EkiLogic, LOGIC_CONDITIONINPUT_INDEX), 0, 1) {
    Init(aCondition, aTrueInput, aFalseInput);
  }
#endif

  //*************************************
  ConditionInput(Condition* aCondition, Input* aTrueInput, Input* aFalseInput)
    : Input(CreateElementId(EbtInput, EkiLogic, LOGIC_CONDITIONINPUT_INDEX), 0, 1) {
    Init(aCondition, aTrueInput, aFalseInput);
  }

  //*************************************
  void Loop() {
    _valueChanged = false;

    if (_condition->Check()) {
      int value = _trueInput->Value();
      if (_currentValue != value) {
        _currentValue = value;
        _minValue = _trueInput->GetMinValue();
        _maxValue = _trueInput->GetMaxValue();
        _valueChanged = true;
      }
    } else {
      int value = _falseInput->Value();
      if (_currentValue != value) {
        _currentValue = value;
        _minValue = _falseInput->GetMinValue();
        _maxValue = _falseInput->GetMaxValue();
        _valueChanged = true;
      }
    }


#ifdef LOG_LOOP
    if (ValueChanged()) {
      GetLog()->printf("CI(%d):L Vl=%d", _id, _currentValue);
    }
#endif

    // Do prefent condittion changes, last and current has to have the same value
    _lastValue = _currentValue;
  }
};
#endif
