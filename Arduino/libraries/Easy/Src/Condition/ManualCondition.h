//*****************************************************************
//* Class ElseCondition - Header
//*
//* Condition: Invert the result of the condition. With this use
//* it possible to define an "IF ... ELSE ..." Relation using the
//* same condition.
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

#ifndef EASY_MANUALCONDITION_H
#define EASY_MANUALCONDITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Condition.h"


class ManualCondition : public Condition {
public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY 
  ManualCondition(int aId)
    : Condition(aId, CreateElementId(EbtCondition, EkcCompare, CONDITION_MANUAL_INDEX)) {
#ifdef LOG_CREATE
    GetLog()->printf("MC(%d):C", _id);
#endif
  }
#endif

  //*************************************
  ManualCondition() 
    : Condition(CreateElementId(EbtCondition, EkcCompare, CONDITION_MANUAL_INDEX)) {
#ifdef LOG_CREATE
    GetLog()->printf("MC(%d):C", _id);
#endif
  }

  //*************************************
  void Loop() {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("MC(%d):L", _id);
#endif

    _lastCheck = _currentCheck;
    
#ifdef LOG_LOOP
    if (CheckChanged()) {
      GetLog()->printf("MC(%d):L Ck=%d", _id, _currentCheck);
    }
#endif
  }
  
  void SetCondition(bool aCondition)
  {
    _lastCheck = _currentCheck;    
    _currentCheck = aCondition;
  }
};
#endif
