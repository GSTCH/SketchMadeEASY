//*****************************************************************
//* Class IteratorValue - Header
//*
//* Input - Iterator steps by StepWidth between FromValue and ToValue. 
//* ECycleMode defines the kind and direction.
//* StepTimeWidthMSec defines the duration of each step. 
//* Used e.g. to tests motors from MinSpeed to MaxSpeed, Servo 
//* between two angles, .... 
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

#ifndef EASY_ITERATORVALUE_H
#define EASY_ITERATORVALUE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

#ifndef DEFAULT_STEP_TIME_WIDTH_MSEC
#define DEFAULT_STEP_TIME_WIDTH_MSEC 50
#endif

class IteratorValue : public Input {
private:
  int _stepWidth; // ReadOnly
  ECycleMode _cycleMode; // ReadOnly
  int _stepTimeWidthMSec; 
  unsigned long _lastStepChange = 0;
  int _minRange;
  int _maxRange;

  //*************************************
  void init(int aFromValue, int aToValue, int aStepWidth, int aStepTimeWidthMSec, ECycleMode aCycleMode) {
#ifdef LOG_SETUP
    GetLog()->printf("IV(%d):C (%d; <%d, %d)", _id, aFromValue, aToValue, aStepWidth);
#endif
    _cycleMode = aCycleMode;
    _lastValue = aFromValue;
    _currentValue = aFromValue;
    _minValue = aFromValue;
	_minRange = aFromValue;
    _maxValue = aToValue;
	_maxRange = aToValue;
    _stepWidth = aStepWidth;
    _stepTimeWidthMSec = aStepTimeWidthMSec;
  }

public:
   //*************************************
 #ifdef CREATE_ID_MANUALLY   
  IteratorValue(int aId, int aFromValue, int aToValue, int aStepWidth = 1, int aStepTimeWidthMSec = DEFAULT_STEP_TIME_WIDTH_MSEC, ECycleMode aCycleMode = cmMin2Max_Min2Max)
    : Input(aId, CreateElementId(EbtInput, EkiHelper, INHELPER_ITERATORVALUE_INDEX), aFromValue, aToValue) {
    init(aFromValue, aToValue, aStepWidth, aStepTimeWidthMSec, aCycleMode);
  }
#endif

  //*************************************
  IteratorValue(int aFromValue, int aToValue, int aStepWidth = 1, int aStepTimeWidthMSec = DEFAULT_STEP_TIME_WIDTH_MSEC, ECycleMode aCycleMode = cmMin2Max_Min2Max)
    : Input(CreateElementId(EbtInput, EkiHelper, INHELPER_ITERATORVALUE_INDEX), aFromValue, aToValue) {
    init(aFromValue, aToValue, aStepWidth, aStepTimeWidthMSec, aCycleMode);
  }

  //*************************************
  void Loop() {
    unsigned long currentTime = millis();
    if (currentTime < _lastStepChange + _stepTimeWidthMSec) {
      return;
    }

    _lastStepChange = currentTime;

    switch (_cycleMode) {
      case cmMin2Max_Min2Max:
        _lastValue = _currentValue;
        _currentValue += _stepWidth;
        if (_currentValue > _maxRange) {
          _currentValue = _minRange;
        }
        break;
      case cmMin2Max2Min:
        _lastValue = _currentValue;
        _currentValue += _stepWidth;
        
        if (_currentValue > _maxRange) {
          _currentValue = _maxRange;
          _stepWidth *= -1;
        } else if (_currentValue < _minRange) {
          _currentValue = _minRange;
          _stepWidth *= -1;
        }
        break;
    }

#ifdef LOG_LOOP
  GetLog()->printf("IV(%d):L V=%d", _id, _currentValue );
#endif
  }
};
#endif
