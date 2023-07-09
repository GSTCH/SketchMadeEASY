//*****************************************************************
//* Class LogicCondition - Header
//*
//* Condition combines two compare condition wtih a logic operator.
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

#ifndef EASY_LGICCONDITION_H
#define EASY_LGICCONDITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"
#include "..\Kernel\Condition.h"

enum ELogicOperator {
  LgAND = 1,
  LgOR = 2,
  LgANDNOT = 3,
};

class LogicCondition : public Condition
{
  private:
    //*************************************
    void Init(Input* aInput1, ECompareOperator aCompareOperator1, int aCompareParameter1,
              ELogicOperator aLogicOperator,
              Input* aInput2, ECompareOperator aCompareOperator2,  int aCompareParameter2)
    {
      _condition1 = new CompareCondition(aInput1, aCompareOperator1, aCompareParameter1);
      _condition2 = new CompareCondition(aInput2, aCompareOperator2, aCompareParameter2);
      _logicOperator = aLogicOperator;

#ifdef LOG_SETUP
      GetLog()->printf("LC(%d):C [Op=%d, Val=%d, Inp=%d], [Op=%d, Val=%d, Inp=%d], %d", _id, aCompareOperator1, aCompareParameter1, aInput1->GetId(), aCompareOperator2, aCompareParameter2, aInput2->GetId(), aLogicOperator );
#endif
    }

  protected:
    Condition* _condition1;
    Condition* _condition2;
    ELogicOperator _logicOperator;

    //*************************************
    bool CheckLogicCondition(bool aCondition1, bool aCondition2, ELogicOperator aLogicOperator)
    {
      switch (aLogicOperator)
      {
        case LgAND:
          return aCondition1 && aCondition2;
        case LgOR:
          return aCondition1 || aCondition2;
        case LgANDNOT:
          return aCondition1 && ! aCondition2;
      }
      return false;
    }

  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY	
    LogicCondition(int aId, Input* aInput1, ECompareOperator aCompareOperator1, int aCompareParameter1,
                   ELogicOperator aLogicOperator,
                   Input* aInput2, ECompareOperator aCompareOperator2,  int aCompareParameter2
                  )  : Condition(aId, CreateElementId(EbtCondition, EkcCompare, CONDITION_LOGIC_INDEX))
    {
      Init(aInput1, aCompareOperator1, aCompareParameter1, aLogicOperator,
           aInput2, aCompareOperator2, aCompareParameter2);
    }
#endif

    //*************************************
    LogicCondition(Input* aInput1, ECompareOperator aCompareOperator1, int aCompareParameter1,
                   ELogicOperator aLogicOperator,
                   Input* aInput2, ECompareOperator aCompareOperator2,  int aCompareParameter2
                  )  : Condition(CreateElementId(EbtCondition, EkcLogic, CONDITION_LOGIC_INDEX))
    {
      Init(aInput1, aCompareOperator1, aCompareParameter1, aLogicOperator,
           aInput2, aCompareOperator2, aCompareParameter2);
    }

    //*************************************
    LogicCondition(Condition* aCondition1, ELogicOperator aLogicOperator, Condition* aCondition2)
      : Condition(CreateElementId(EbtCondition, EkcLogic, CONDITION_LOGIC_INDEX))
    {
      _condition1 = aCondition1;
      _condition2 = aCondition2;
      _logicOperator = aLogicOperator;

#ifdef LOG_SETUP
      GetLog()->printf("LC(%d):C(%d) CD1(=%d), CD2=(%d), Op=%d", _id, _condition1->GetId(), _condition2->GetId(), aLogicOperator );
#endif
    }

    //*************************************
    void Loop()
    {
      _lastCheck = _currentCheck;

      _currentCheck = CheckLogicCondition(_condition1->Check(), _condition2->Check(), _logicOperator );
      if (CheckChanged() && _currentCheck)
      {
#ifdef LOG_LOOP
        GetLog()->printf("LC(%d):Ck Ck1=%d Ck2=%d", _id, _condition1->Check(), _condition2->Check() );
#endif
      }
      else
      {
#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("LC(%d):Ck failed Ck1=%d Ck2=%d", _id, _condition1->Check(), _condition2->Check() );
#endif
      }
    }
};
#endif
