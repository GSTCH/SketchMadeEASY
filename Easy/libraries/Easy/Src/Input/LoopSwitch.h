//*****************************************************************
//* Class LoopButton - Header
//*
//* A shift register control by a a signal (e.g. button): The value 
//* iterate through a defined range (MIN...MAX). When pin is high
//* the value increases by step width.
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#ifndef EASY_LOOPSWITCH_H
#define EASY_LOOPSWITCH_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"


//*****************************************************************

class LoopSwitch : public Input
{
  protected:
    int _pin; // ReadyOnly
	unsigned long _debounceTimeMSec; // ReadOnly
    unsigned long _ignoreChangeMillis;
	ESwitchResistoreMode _switchResistoreMode;  // ReadyOnly
    byte _switchPressed; // ReadyOnly
    int _stepWidth; // ReadyOnly
    int _currentPinValue;
    int _lastPinValue;
    
	//*************************************
    void Init(int aPin, int aMinValue, int aMaxValue, int aStepWidth, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec)
    {
      _pin = aPin;
      _stepWidth = aStepWidth;

      _lastPinValue = 0;
      _currentPinValue = 0;
      _ignoreChangeMillis = 0;
	  _switchResistoreMode = aSwitchResistoreMode;
	  _debounceTimeMSec = aDebounceTimeMSec;

      _currentValue = aMinValue;
	  
	  if (_switchResistoreMode == smPullUpExternal) {
        //PullUp - Switch pressed sets pin to high
        _switchPressed = HIGH;
      } else {
	    // PullDown - Swich pressed is low.
	    _switchPressed = LOW;
      }
    }

  public:
    //*************************************
  #ifdef CREATE_ID_MANUALLY   
    LoopSwitch(int aId, int aPin, int aMinValue, int aMaxValue, int aStepWidth, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec) : Input(aId, CreateElementId(EbtInput, EkiDigital, DIGITAL_LOOPSWITCH_INDEX), aMinValue, aMaxValue)
    {
      Init(aPin, aMinValue, aMaxValue, aStepWidth, aSwitchResistoreMode, aDebounceTimeMSec);
    }
  #endif  
  
  //*************************************
    LoopSwitch(int aPin, int aMinValue, int aMaxValue, int aStepWidth, ESwitchResistoreMode aSwitchResistoreMode = smPullDownInternal, int aDebounceTimeMSec = EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC) : Input(CreateElementId(EbtInput, EkiDigital, DIGITAL_LOOPSWITCH_INDEX), aMinValue, aMaxValue)
    {
      Init(aPin, aMinValue, aMaxValue, aStepWidth, aSwitchResistoreMode, aDebounceTimeMSec);
    }

    //*************************************
    void Setup()
    {
#ifdef LOG_SETUP
      GetLog()->printf("LS(%d):S P=%d", _id, _pin );
#endif

 	  if (_switchResistoreMode == smPullDownInternal) {
        // Set internal PullUp mode to the pins
        pinMode(_pin, INPUT_PULLUP);
		
        // turn on pullup resistors
        digitalWrite(_pin, HIGH);
      } else {
        // Set external mode to the pins
        pinMode(_pin, INPUT);
      }
    }

    //*************************************
    void Loop()
    {
	  unsigned long currentTime =millis();
		  
	  if (_ignoreChangeMillis > currentTime)
      {
#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("LS(%d):L Debounce", _id);
#endif
        return;
      }

      _lastValue = _currentValue;
      _lastPinValue = _currentPinValue;

      _currentPinValue = digitalRead(_pin);

#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("LS(%d):L P=%d", _id,  _currentPinValue);
#endif

      if (_currentPinValue == _switchPressed)
      {
        if (_lastPinValue != _currentPinValue)
        {
#ifdef LOG_LOOP
          GetLog()->printf("LS(%d):L Vl=%d", _id, _currentValue );
#endif

          _currentValue = _currentValue + _stepWidth;
          if (_currentValue > _maxValue)
          {
            _currentValue = _minValue;
          }

          _ignoreChangeMillis = currentTime + _debounceTimeMSec;
        }
      }
      else // if (_currentPinValue == _switchNotPressed )
      {
		// Debounce the release of the button
        if (_lastPinValue != _currentPinValue)
        {
#ifdef LOG_LOOP
          GetLog()->printf("LS(%d):L Vl=0", _id );
#endif
          _ignoreChangeMillis = currentTime + _debounceTimeMSec;
        }
      }
    }
};

#endif
