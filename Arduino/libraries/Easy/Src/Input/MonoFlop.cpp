//*****************************************************************
//* Class Monoflop - Implementation
//*
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

#include "MonoFlop.h"

#define ARDUINO_STARTUP_TIME_MS 1000

//*************************************
#ifdef CREATE_ID_MANUALLY 
MonoFlop::MonoFlop(int aId, int aPin, int aHighDelay, int aLowDelay, bool aStart, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec) : Input(aId, CreateElementId(EbtInput, EkiDigital, DIGITAL_MONOFLOP_INDEX), mfStateLow, mfStateHighTimerEnd )
{
  Init(aPin, aHighDelay, aLowDelay, aStart, aSwitchResistoreMode, aDebounceTimeMSec);
}
#endif

//*************************************
MonoFlop::MonoFlop(int aPin, int aHighDelay, int aLowDelay, bool aStart, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec) : Input(CreateElementId(EbtInput, EkiDigital, DIGITAL_MONOFLOP_INDEX), mfStateLow, mfStateHighTimerEnd )
{
  Init(aPin, aHighDelay, aLowDelay, aStart, aSwitchResistoreMode, aDebounceTimeMSec);
}

//*************************************
void MonoFlop::Init(int aPin, int aHighDelay, int aLowDelay, bool aStart, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec)
{
#ifdef LOG_SETUP
  GetLog()->printf("MF(%d):C Id=%d P=%d, HD=%d, LD=%d, T=%d, RM=%d", _id, aPin, aHighDelay, aLowDelay, aDebounceTimeMSec, aSwitchResistoreMode);
#endif
	
  _pin = aPin;
  _debounceTimeMSec = aDebounceTimeMSec;
  
  if (aHighDelay > _debounceTimeMSec)
  {
    _highDelay = aHighDelay;
  }
  else
  {
    _highDelay = _debounceTimeMSec;
  }

  if (aLowDelay > _debounceTimeMSec)
  {
    _lowDelay = aLowDelay;
  }
  else
  {
    _lowDelay = _debounceTimeMSec;
  }

  _lastPinValue = 0;
  _currentPinValue = 0;
  _ignoreChangeMillis = 0;
  
  _switchResistoreMode = aSwitchResistoreMode;
  if (_switchResistoreMode == smPullUpExternal) 
  {
    //PullUp - Switch pressed sets pin to high
    _switchPressed = HIGH;
	_switchNotPressed = LOW;
  } 
  else 
  {
	  // PullDown - Switch not pressed is high.
	_switchPressed = LOW;
	_switchNotPressed = HIGH;
  }
  
  _currentValue = mfStateLowTimerEnd;
  _lastValue = mfStateLowTimerEnd;
  _monoflopEndTime = 0;
  _autoStartup = aStart;
}

//*************************************
void MonoFlop::Setup()
{
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("MF(%d):S P=%d", _id, _pin );
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
void MonoFlop::Loop()
{
  _lastValue = _currentValue;
  _lastPinValue = _currentPinValue;

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("MF(%d):L Vl=%d", _id, _currentValue);
#endif

  unsigned long currentTime = millis();

  if (_currentValue == mfStateHigh)
  {
    _currentValue = mfStateHighTimerRun;
    _monoflopEndTime = currentTime + _highDelay;

#ifdef LOG_LOOP
    GetLog()->printf("MF(%d):L CVl=%d", _id,  _currentValue);
#endif
    return;
  }
  else if (_currentValue == mfStateLow)
  {
    _currentValue = mfStateLowTimerRun;
    _monoflopEndTime = currentTime + _lowDelay;
#ifdef LOG_LOOP
    GetLog()->printf("MF(%d):L CVl=%d", _id,  _currentValue);
#endif
    return;
  }

  if (currentTime > _monoflopEndTime)
  {
    if (_currentValue == mfStateLowTimerRun)
    {
      _currentValue = mfStateLowTimerEnd;
#ifdef LOG_LOOP
      GetLog()->printf("MF(%d):L CVl=%d", _id,  _currentValue);
#endif
      return;
    }
    else if (_currentValue == mfStateHighTimerRun)
    {
      _currentValue = mfStateHighTimerEnd;
#ifdef LOG_LOOP
      GetLog()->printf("MF(%d):L CVl=%d", _id,  _currentValue);
#endif
      return;
    }
  }

  if (_ignoreChangeMillis > currentTime)
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MF(%d):L debounce", _id);
#endif
    return;
  }

  _currentPinValue = digitalRead(_pin);
  
  if (_currentPinValue==LOW && _autoStartup)
  {
	  _currentValue = mfStateHigh;
      _autoStartup = false;	   
	  return;
  }
  else if (_currentPinValue==HIGH && _autoStartup)
  {
	  _currentValue = mfStateHighTimerEnd;
      _autoStartup = false;	   
	  return;
  }  
  
  if (_currentPinValue != _lastPinValue)
  {
    _ignoreChangeMillis = currentTime + _debounceTimeMSec;
  }

  if (_currentValue == mfStateLowTimerEnd && _currentPinValue == _switchPressed)
  {
    _currentValue = mfStateHigh;
#ifdef LOG_LOOP
    GetLog()->printf("MF(%d):L CVl=%d", _id,  _currentValue);
#endif
  }
  else if (_currentValue == mfStateHighTimerEnd && _currentPinValue == _switchNotPressed)
  {
    _currentValue = mfStateLow;
#ifdef LOG_LOOP
    GetLog()->printf("MF(%d):L CVl=%d", _id,  _currentValue);
#endif
  }
}
