//*****************************************************************
//* Class RemoteMonoFlop - Header
//*
//* Input - When set value greather than 0, it stay for aIntervalMSec,
//* then it goes back to 0
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

#ifndef REMOTE_MONOFLOP_H
#define REMOTE_MONOFLOP_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

class RemoteMonoFlop : public RemoteInput {
private:
  //*************************************
  void init(unsigned long aIntervalMSec) {
#ifdef LOG_SETUP
    GetLog()->printf("RM(%d):C Dur=%d", _id, aIntervalMSec);
#endif
    _intervalMSec = aIntervalMSec;
  }

protected:
  unsigned long _intervalMSec;
  unsigned long _lastStateChangeMilli;
  
public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY    
  RemoteMonoFlop(int aId, unsigned long aIntervalMSec)
    : RemoteInput(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_REMOTEMONOFLOP_INDEX), 0, !0) {
    init(aIntervalMSec);
  }
#endif

  //*************************************
  RemoteMonoFlop(unsigned long aIntervalMSec)
    : RemoteInput(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_REMOTEMONOFLOP_INDEX), 0, !0) {
    init(aIntervalMSec);
  }

  //*************************************
  void Setup() {
  }
  
  //*************************************
  void SetValue(int aValue) {
    if (aValue>0 && _lastStateChangeMilli==0)
    {
     _currentValue=aValue;
     _lastStateChangeMilli = millis(); 
    }
    else if (aValue==0)
    {
      _lastStateChangeMilli=0;
      _currentValue=0;
    }
  }

  //*************************************
  void Loop() {
    _lastValue = _currentValue;
    
    if (_lastStateChangeMilli==0)
    {
      return;
    }

    unsigned long currentTime = millis();
    if (currentTime > _lastStateChangeMilli + _intervalMSec)
    {
#ifdef LOG_LOOP
      GetLog()->printf("RM(%d):C End", _id);
#endif      
      _currentValue = 0;
      _lastStateChangeMilli = 0;
    }
  }

  static const int High = 1;
  static const int Low = 0;

  static const int On = 1;
  static const int Off = 0;
};

#endif
