//*****************************************************************
//* Class SignalCountingRelation - Header
//*
//* After a start condition is true, the relation beginns to work.
//* The Actuator is acts, until N steops are counted at an input
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

#ifndef EASY_SIGNALCOUNTINGRELATION_H
#define EASY_SIGNALCOUNTINGRELATION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"
#include "..\Kernel\Actuator.h"
#include "..\Condition\ManualCondition.h"

class SignalCountingRelation : public Relation {
private:
  Condition* _startCondition= NULL;
  Condition* _countCondition= NULL;
  Input* _amountOfSignal = NULL;
  Actuator* _actuator= NULL;
  int _waitUntilAcceptNextInputMSec; // ReadyOnly  
  ManualCondition* _state;
   
  bool _iterationActive = false;
  unsigned long _ignoreInputChange;
  int _downCounter = 0;

  //*************************************
  void init(Condition* aStartCondition, Input* aAmountOfSignal, Condition* aCountCondition, Actuator* aActuator, int aWaitUntilAcceptNextInputMSec)
  {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("SCR(%d):C SC=%d, Cn=%d, ActId=%d, Am=%d, %d)", _id, aStartCondition->GetId(), aCountCondition->GetId(), aActuator->GetId(), aAmountOfSignal->GetId(), aWaitUntilAcceptNextInputMSec);
#endif
    _startCondition = aStartCondition;
    _countCondition = aCountCondition;    
    _amountOfSignal = aAmountOfSignal;
    _actuator = aActuator;   
    _waitUntilAcceptNextInputMSec = aWaitUntilAcceptNextInputMSec;        
    
    Active = new FixValue(ReadyToStart, ReadyToStart, DownCounterActive);
    _state = new ManualCondition();
    _condition = _state;
  }

public:
  //*************************************   
  static const int DownCounterActive = 1;
  static const int ReadyToStart = 0;

  FixValue* Active = NULL;
  
 #ifdef CREATE_ID_MANUALLY   
  SignalCountingRelation(int aId, Condition* aStartCondition, Condition* aCountCondition, Input* aAmountOfSignal, Actuator* aActuator, int aWaitUntilAcceptNextInputMSec) : Relation(aId, CreateElementId(EbtRelation, EkrLogic, SIGNALCOUNTINGRELATION_INDEX), new ManualCondition())
  {
    init(aStartCondition, aAmountOfSignal, aCountCondition, aActuator, aWaitUntilAcceptNextInputMSec);
  } 
#endif

  //*************************************
  SignalCountingRelation(Condition* aStartCondition, Condition* aCountCondition, Input* aAmountOfSignal, Actuator* aActuator, int aWaitUntilAcceptNextInputMSec) : Relation(CreateElementId(EbtRelation, EkrLogic, SIGNALCOUNTINGRELATION_INDEX), NULL)
  {
    init(aStartCondition, aAmountOfSignal, aCountCondition, aActuator, aWaitUntilAcceptNextInputMSec);
  }   

  //*************************************
  void Loop() {    
    if (!_iterationActive)
    {
      if (_startCondition->Check())
      {
        _iterationActive = true;

        Active->SetValue(DownCounterActive);
        _downCounter = _amountOfSignal->Value();
        
#ifdef LOG_LOOP
        GetLog()->printf("SCR(%d):L SC=1, DC=%d", _id, _downCounter );
#endif
        
        _state->SetCondition(true);       
        _actuator->Act(FixValue::On());
        
        _ignoreInputChange = millis() + _waitUntilAcceptNextInputMSec;
      }
      else
      {
        // Return an try next time, if start condition is true.
        SetRelationState(false);
        return; 
      }
    }
    else
    {
      unsigned long time = millis();
      if (time <_ignoreInputChange)
      {
        // Waiting time until signal change is considered again, still active        
        SetRelationState(_iterationActive);
        return;
      }      
      
      if (_countCondition->CheckChanged() && _countCondition->Check())
      {
        _downCounter--;
      
        if (_downCounter<=0)
        {
#ifdef LOG_LOOP
          GetLog()->printf("SCR(%d):L 0", _id);
#endif

          _iterationActive = false;
          _ignoreInputChange = 0;

          _state->SetCondition(false);  
          _actuator->Act(FixValue::Off());                   
        }  
        else
        {
#ifdef LOG_LOOP
          GetLog()->printf("SCR(%d):L %d", _id, _downCounter);
#endif
          
          _ignoreInputChange = millis() + _waitUntilAcceptNextInputMSec;          
        }
      }      
    }
    
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SCR(%d):L V=%d", _id, _downCounter );
#endif

    SetRelationState(_iterationActive);
  } 
};
#endif
