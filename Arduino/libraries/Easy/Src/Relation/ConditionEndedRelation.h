
//*****************************************************************
//* Class ConditionEndedActuator - Header
//*
//* Condition ended relation - Logic like a monoflop with logic end.
//* If wrapped ActivLogic changes to false, it remains at the true  
//* until the endcondition is true. 
//* Example: When power off, position a motor using a limit switch.
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2024 by Hans Rothenbuehler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************

#ifndef EASY_CONDITIONENDEDRELATION_H
#define EASY_CONDITIONENDEDRELATION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Relation.h"
#include "..\Kernel\Input.h"

class ConditionEndedRelation : public Relation
{
private:
  //*************************************
  inline void Init(Condition* aEndCondition, Actuator* aActuator, Input* aActuatorParameterTrue, Input* aActuatorParameterFalse)
  {
#ifdef LOG_SETUP
    GetLog()->printf("CER(%d):C Ac=%d, EC=%d", _id, aActuator->Id, aEndCondition != NULL);
#endif
    _endCondition = aEndCondition;
    _actuator = aActuator;
    _actuatorParameterTrue = aActuatorParameterTrue;
    _actuatorParameterFalse = aActuatorParameterFalse;
  }

  bool _conditionStopActive = false;

protected:
  Condition* _endCondition;
  Actuator* _actuator = NULL;
  Input* _actuatorParameterTrue = NULL;
  Input* _actuatorParameterFalse = NULL;

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY 	
  ConditionEndedRelation(int aId, Condition* aActiveCondition, Condition* aEndCondition, Actuator* aActuator, Input* aActuatorParameterTrue, Input* aActuatorParameterFalse) : Relation(aId, CreateElementId(EbtRelation, EkcLogic, CONDITION_ENDED_RELATION), aActiveCondition)
  {
    Init(aEndCondition, aActuator, aActuatorParameterTrue, aActuatorParameterFalse);
  }
#endif

  //*************************************
  ConditionEndedRelation(Condition* aActiveCondition, Condition* aEndCondition, Actuator* aActuator, Input* aActuatorParameterTrue, Input* aActuatorParameterFalse) : Relation(CreateElementId(EbtRelation, EkrLogic, CONDITION_ENDED_RELATION), aActiveCondition)
  {
    Init(aEndCondition, aActuator, aActuatorParameterTrue, aActuatorParameterFalse);
  }

  ConditionEndedRelation(Condition* aActiveCondition, Condition* aEndCondition, Actuator* aActuator) : Relation(CreateElementId(EbtRelation, EkrLogic, CONDITION_ENDED_RELATION), aActiveCondition)
  {
    Init(aEndCondition, aActuator, FixValue::On(), FixValue::Off());
  }

  //*************************************
  void Setup()
  {
#ifdef LOG_SETUP
    GetLog()->printf("CER(%d):S", _id);
#endif
  }

  //*************************************
  void Loop()
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("CER(%d):L", _id);
#endif

    if (_condition->CheckChanged() && _condition->Check())
    {
      // Active condition changed to true
#ifdef LOG_LOOP
      GetLog()->printf("CER(%d):L C=0, Ac=1", _id);
#endif

      _actuator->Act(_actuatorParameterTrue);
      _conditionStopActive = false;
      SetRelationState(true);
    }
    else if (_condition->CheckChanged() && !_condition->Check())
    {
      // Active condition changed to false
      _conditionStopActive = true;

#ifdef LOG_LOOP
      GetLog()->printf("CER(%d):L C=0", _id);
#endif
    }

    if (_conditionStopActive)
    {
      if ((_endCondition == NULL) || (_endCondition->CheckChanged() && _endCondition->Check()))
      {
#ifdef LOG_LOOP
        GetLog()->printf("CER(%d):L Ac=0+", _id);
#endif
        _actuator->Act(_actuatorParameterFalse);
        _conditionStopActive = false;
        SetRelationState(false);
      }
    }
  }
};
#endif
