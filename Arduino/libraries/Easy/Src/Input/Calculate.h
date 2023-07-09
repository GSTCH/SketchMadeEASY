//*****************************************************************
//* Class Calculate - Header
//*
//* Tool class to make some simple mathematic calculations.
//* Syntax is "Result = Input1 Operator Input2"
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

#ifndef Calculate_h
#define Calculate_h

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\Input.h"

enum EMathOperator {
  OpPlus = 1,
  OpMinus = 2,
  OpDivideFloat = 3,
  OpDivideInt = 4,
  OpModulo = 5,
  OpTimes = 6
};

class Calculate : public Input {
private:
  //*************************************
  void Init(Input* aInput1, Input* aInput2, EMathOperator aOperator) {
    _input1 = aInput1;
    _input2 = aInput2;
    _operator = aOperator;

    int minOfBoth = min(_input1->GetMinValue(), _input2->GetMinValue());
    int maxOfBoth = max(_input1->GetMaxValue(), _input2->GetMaxValue());

    switch (_operator) {
      case OpPlus:
        _minValue = _input1->GetMinValue() + _input2->GetMinValue();
        _maxValue = _input1->GetMaxValue() + _input2->GetMaxValue();
        break;
      case OpMinus:
        _minValue = minOfBoth - maxOfBoth;
        _maxValue = maxOfBoth - minOfBoth;
        break;
      case OpDivideFloat:
        _minValue = maxOfBoth / minOfBoth;
        _maxValue = minOfBoth / maxOfBoth;
        break;
      case OpDivideInt:
        _minValue = floor(maxOfBoth / minOfBoth);
        _maxValue = floor(minOfBoth / maxOfBoth);
        break;
      case OpModulo:
        _minValue = 0;
        _maxValue = maxOfBoth - 1;
        break;
      case OpTimes:
        _minValue = _input1->GetMinValue() * _input2->GetMinValue();
        _maxValue = _input1->GetMaxValue() * _input2->GetMaxValue();
        break;
    }
  }

protected:
  Input* _input1;
  Input* _input2;
  EMathOperator _operator;

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY     
  Calculate(int aId, Input* aInput1, Input* aInput2, EMathOperator aOperator)
    : Input(aId, CreateElementId(EbtInput, EkiHelper, INHELPER_CALCULATE_INDEX), 0, 0) {
    Init(aInput1, aInput2, aOperator);
  }
#endif

  //*************************************
  Calculate(Input* aInput1, Input* aInput2, EMathOperator aOperator)
    : Input(CreateElementId(EbtInput, EkiHelper, INHELPER_CALCULATE_INDEX), 0, 0) {
    Init(aInput1, aInput2, aOperator);
  }

  //*************************************
  void Loop() {
    _lastValue = _currentValue;
    switch (_operator) {
      case OpPlus:
        _currentValue = _input1->Value() + _input2->Value();
        break;
      case OpMinus:
        _currentValue = _input1->Value() - _input2->Value();
        break;
      case OpDivideFloat:
        _currentValue = _input1->Value() / _input2->Value();
        break;
      case OpDivideInt:
        _currentValue = floor(_input1->Value() / _input2->Value());
        break;
      case OpModulo:
        _currentValue = _input1->Value() % _input2->Value();
        break;
      case OpTimes:
        _currentValue = _input1->Value() * _input2->Value();
        break;
    }
  }
};

#endif
