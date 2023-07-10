//*****************************************************************
//* Class ServoStepperPositionBase - Header
//*
//* Internal base class of angle controlled stepper motors
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

#ifndef EASY_SERVOSTEPPERPOSITIONBASE_H
#define EASY_SERVOSTEPPERPOSITIONBASE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\ServoBase.h"

#ifndef EASY_INITIALIZE_DELAY_BETWEEN_STEP_MSEC
#define EASY_INITIALIZE_DELAY_BETWEEN_STEP_MSEC 200
#endif

class ServoStepperPositionBase : public ServoBase {
private:
  EInitializeMode _initializeMode;
  int _homeSwitchPin;
  int _initalizeStepWidth;
  int _sleepUntilNextInitStep;
  ESwitchResistoreMode _homeSwitchResistoreMode;
  int _switchValue;
  Input* _inputActDuringInitialize = NULL;

protected:
  //*************************************
  void Init(EInitializeMode aInitializeMode, int aHomeSwitchPin, int aResolution, ESwitchResistoreMode aHomeSwitchResistoreMode) {
#ifdef LOG_SETUP
    GetLog()->printf("SPB(%d):C I=%d, P=%d, R=%d, M=%d", _id, aInitializeMode, aHomeSwitchPin, aResolution, aHomeSwitchResistoreMode);
#endif
    _sleepUntilNextInitStep = 0;

    switch (aInitializeMode) {
      case spNone:
        _homeSwitchPin = 0;
		_homeSwitchResistoreMode = aHomeSwitchResistoreMode;
        _initalizeStepWidth = 0;
        break;
      case spForward:
        _homeSwitchPin = aHomeSwitchPin;
		_homeSwitchResistoreMode = aHomeSwitchResistoreMode;
        _initalizeStepWidth = round(aResolution / 360.0);
        break;
      case spBackward:
        _homeSwitchPin = aHomeSwitchPin;
		_homeSwitchResistoreMode = aHomeSwitchResistoreMode;
        _initalizeStepWidth = -round(aResolution / 360.0);
        break;		
    }
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("SPB(%d):C SW=%d", _id, _initalizeStepWidth);
#endif
	
  }

  //*************************************
  void GoToHome() {
    int directionSign = 1;
    if (_initalizeStepWidth != 0) {
      int limitSwitch = digitalRead(_homeSwitchPin);

      if (limitSwitch != _switchValue) {
        unsigned long currentTime = millis();
        if (currentTime < _sleepUntilNextInitStep) {
          return;
        }

#ifdef LOG_SETUP
        GetLog()->printf("SPB(%d):GH LS=%d, SW=%d", _id, limitSwitch, _initalizeStepWidth);
#endif
        _servoShield->step(_initalizeStepWidth);
        _sleepUntilNextInitStep = currentTime + EASY_INITIALIZE_DELAY_BETWEEN_STEP_MSEC;

        //Idea to more be accurate: Turning slowly in the other direction until limit switch is 0. Current accuracy is 1° and for this very well. Pay attention! Need debounce!

      } else {
#ifdef LOG_SETUP_DEBUG
        GetLog()->printf("SPB(%d):GH end", _id);
#endif
        _initalizeStepWidth = 0;
        _servoShield->resetPosition();

        if (_inputActDuringInitialize != NULL) {
          ServoBase::Act(_inputActDuringInitialize);
          _inputActDuringInitialize = NULL;
        }
      }
    }
  }

public:  
  //*************************************
  ServoStepperPositionBase(int aMinAngle, int aMaxAngle, int aResolution, EInitializeMode aInitializeMode = spNone, int aHomeSwitchPin = 0, ESwitchResistoreMode aHomeSwitchResistoreMode = smPullDownInternal)
    : ServoBase(aMinAngle, aMaxAngle, CreateElementId(EbtActuator, EkaServo, SERVO_STEPPERPOSITION_INDEX)) {
    Init(aInitializeMode, aHomeSwitchPin, aResolution, aHomeSwitchResistoreMode);
  }

  //*************************************
  void Setup() {
    ServoBase::Setup();

    if (_homeSwitchPin > 0) {
      switch(_homeSwitchResistoreMode)
	  {
	    case smPullDownInternal:
		  pinMode(_homeSwitchPin, INPUT_PULLUP);
		  _switchValue = LOW;
		  break;
		case smPullDownExternal:
		  pinMode(_homeSwitchPin, INPUT);
		  _switchValue = LOW;
		  break;
		case smPullUpExternal:
		  pinMode(_homeSwitchPin, INPUT);
		  _switchValue = HIGH;
		  break;
	  }
    }
  }

  //*************************************
  void Loop() {
    if (_initalizeStepWidth != 0) {
      GoToHome();
      _servoShield->Loop();
    } else {
      ServoBase::Loop();
    }
  }

  //*************************************
  void Act(Input* aInput) {
    if (_initalizeStepWidth == 0) {
      ServoBase::Act(aInput);
    } else {
      _inputActDuringInitialize = aInput;
    }
  }
};

#endif
