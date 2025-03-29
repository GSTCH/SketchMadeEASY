//*****************************************************************
//* Class Relation1to1 - Header
//*
//* Relation between input and actuator. Calls act of actuator, when 
//* condition is true. A NULL Condition is allways true.
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

#ifndef EASY_RELATION1TO1_H
#define EASY_RELATION1TO1_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Relation.h"
#include "..\Kernel\Actuator.h"
#include "..\Kernel\Condition.h"
#include "..\Kernel\Input.h"
#include "..\Common\ActuatorCollectionItem.h"

class Relation1to1 : public Relation
{
private:
  void init(Condition* aCondition, Actuator* aActuator, Input* aActionParameter)
  {
#ifdef LOG_SETUP
    GetLog()->printf("R1(%d):C AcId=%d", _id, aActuator->GetId());
#endif
    _itemCount = 1;
    _actionItems = new ActuatorCollectionItem * [_itemCount];
    _actionItems[0] = new ActuatorCollectionItem(aActuator, aActionParameter);
  }
protected:
  ActuatorCollectionItem** _actionItems = NULL;
  int _itemCount = 0;

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY	
  Relation1to1(int aId, Condition* aCondition, Actuator* aActuator, Input* aActionParameter) : Relation(aId, CreateElementId(EbtRelation, EkrCompare, COMPARE_1TO1_INDEX), aCondition)
  {
    init(aCondition, aActuator, aActionParameter);
  }
#endif

  //*************************************
  Relation1to1(Condition* aCondition, Actuator* aActuator, Input* aActionParameter) : Relation(CreateElementId(EbtRelation, EkrCompare, COMPARE_1TO1_INDEX), aCondition)
  {
    init(aCondition, aActuator, aActionParameter);
  }

  //*************************************
  Relation1to1(Condition* aCondition, ActuatorCollectionItem** aActionItems, int aItemCount) : Relation(CreateElementId(EbtRelation, EkrCompare, COMPARE_1TO1_INDEX), aCondition)
  {
    _itemCount = aItemCount;
    _actionItems = aActionItems;
  }

  //*************************************
  virtual void Loop()
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("R1(%d):L", _id);
#endif

#ifdef LOG_LOOP_DEBUG
    if (_condition != NULL)
    {
      if (_condition->CheckChanged())
      {
        GetLog()->printf("R1(%d):L Ck=%d, CCk=%d", _id, _condition->Check(), _condition->CheckChanged());
      }
    }
#endif

    bool actionParameterChanged = false;
    for (int idx = 0; idx < _itemCount; idx++)
    {
#ifdef LOG_LOOP_DEBUG
      if (_actionItems!=NULL && _actionItems[idx]->ValueChanged())
      {
        GetLog()->printf("R1(%d):L VC[%d]=%d", _id, idx, _actionItems[idx]->ValueChanged());
      }
#endif              
      actionParameterChanged |= (_actionItems!= NULL && _actionItems[idx]->ValueChanged());
    }

    bool CheckWithoutCondition = _condition == NULL && actionParameterChanged;
    bool CheckWithCondition = _condition != NULL && _condition->Check() && (_condition->CheckChanged() || actionParameterChanged);
    if (CheckWithoutCondition || CheckWithCondition)
    {
#ifdef LOG_LOOP_DEBUG
      if (CheckWithCondition)
      {
        GetLog()->printf("R1(%d):L Ck=%d, PCg=%d", _id, _condition->Check(), actionParameterChanged);
      }
      else
      {
        GetLog()->printf("R1(%d):L Call PCg=%d", _id, actionParameterChanged);
      }
#endif

      if (_actionItems!=NULL)
	  {
        for (int idx = 0; idx < _itemCount; idx++)
        {
          if (_actionItems[idx]!=NULL)
          { 
            _actionItems[idx]->Act();
          }
        }
	  }

#ifdef LOG_LOOP
      GetLog()->printf("R1(%d):L RS=1", _id);
#endif      
      SetRelationState(true);
    }
    else
    {
      SetRelationState(false);
    }
  }
};
#endif
