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

#ifndef EASY_ELSECONDITION_H
#define ElseCondition_h

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"
#include "..\Kernel\Condition.h"


class ElseCondition : public Condition {
private:
  //*************************************
  inline void init(Condition* aCondition) {
    _condition = aCondition;

#ifdef LOG_CREATE
    GetLog()->printf("EC(%d):C C=%d", _condition->GetId());
#endif
  }

protected:
  Condition* _condition;

public:
  //*************************************
 #ifdef CREATE_ID_MANUALLY 
  ElseCondition(int aId, Condition* aCondition)
    : Condition(aId, CreateElementId(EbtCondition, EkcCompare, CONDITION_ELSE_INDEX)) {
    init(aCondition);
  }
#endif

  //*************************************
  ElseCondition(Condition* aCondition)
    : Condition(CreateElementId(EbtCondition, EkcCompare, CONDITION_ELSE_INDEX)) {
    init(aCondition);
  }

  //*************************************
  void Loop() {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("EC(%d):L", _id);
#endif

    _lastCheck = _currentCheck;

    _currentCheck = !_condition->Check();

#ifdef LOG_LOOP
    if (CheckChanged()) {
      GetLog()->printf("EC(%d):L Ck=%d", _id, _currentCheck);
    }
#endif
  }
};
#endif
