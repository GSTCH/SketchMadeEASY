//*****************************************************************
//* Class RemoteVariableInput - Header
//*
//* Represent a combination of an analog input and
//* switch with three position. FlySky: VrA+SwB or VrB+SwB
//*
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2025 by Hans Rothenbuehler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************

#ifndef EASY_REMOTEVARIABLEINPUTSWITCH
#define EASY_REMOTEVARIABLEINPUTSWITCH

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Input.h"
#include "..\Kernel\RemoteControl.h"
#include "..\Input\VariableInput.h"

#ifndef ARDUINO_MAX_PWM_IN
  #define ARDUINO_MAX_PWM_IN 1023
#endif

class RemoteVariableInputSwitch : public Input
{
  private:
    RemoteInput* _switch3Pos;
    RemoteInput* _variableInput;
    int _lastValueVariable;
    int _currentValueVariable;
    int _lastValueSwitch;
    int _currentValueSwitch;
    
    void Init (RemoteInput* aVariableInput, RemoteInput* a3PosSwitch)
    {
      _switch3Pos = a3PosSwitch;
      _variableInput = aVariableInput;
    }
  protected:

  public:
#ifdef CREATE_ID_MANUALLY  
    RemoteVariableInputSwitch (int aId, RemoteInput* aVariableInput, RemoteInput* a3PosSwitch )
     : Input(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VARIABLEINPUTSWITCH_INDEX), -ARDUINO_MAX_PWM_IN, ARDUINO_MAX_PWM_IN)
     {
        Init(aVariableInput, a3PosSwitch);
     }

     RemoteVariableInputSwitch (int aId, RemoteControl* aRemoteControl, ERcControl aVariableInput = rcVrB, ERcControl aDirectionSwitch = rcSwC)
     : Input(aId, CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VARIABLEINPUTSWITCH_INDEX), -ARDUINO_MAX_PWM_IN, ARDUINO_MAX_PWM_IN)
     {
        Init(aRemoteControl->getControl(aVariableInput), aRemoteControl->getControl(aDirectionSwitch));
     }     
#endif
    RemoteVariableInputSwitch (RemoteInput* aVariableInput, RemoteInput* a3PosSwitch )
     : Input(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VARIABLEINPUTSWITCH_INDEX), -ARDUINO_MAX_PWM_IN, ARDUINO_MAX_PWM_IN)
    {
        Init(aVariableInput, a3PosSwitch);
    }

    RemoteVariableInputSwitch (RemoteControl* aRemoteControl, ERcControl aVariableInput = rcVrB, ERcControl aDirectionSwitch = rcSwC )
     : Input(CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VARIABLEINPUTSWITCH_INDEX), -ARDUINO_MAX_PWM_IN, ARDUINO_MAX_PWM_IN)
    {
      Init(aRemoteControl->getControl(aVariableInput), aRemoteControl->getControl(aDirectionSwitch));
    }    
	
    void Setup()
    {   
#ifdef LOG_SETUP_DEBUG
      GetLog()->printf("RVS(%d):S", _id );
#endif
    }

    void Loop()
    {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("RVS(%d):L", _id );
#endif
      _lastValueVariable = _currentValueVariable;
      _currentValueVariable = _variableInput->Value();
      _lastValueSwitch = _currentValueSwitch;
      _currentValueSwitch = _switch3Pos->Value();

      if (_lastValueVariable!=_currentValueVariable ||_lastValueSwitch!=_currentValueSwitch)
      {
#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("RVS(%d):L val change Var=%d Sw=%d ", _id, _currentValueVariable, _currentValueSwitch );
#endif

        _lastValue = _currentValue;
        if (_currentValueSwitch == Switch3Position::Pos1)
        {
#ifdef LOG_LOOP
          GetLog()->printf("RVS(%d):L stp", _id );
#endif
          _currentValue = 0;
        }
        else if (_currentValueSwitch == Switch3Position::Pos0)
        {
#ifdef LOG_LOOP
          GetLog()->printf("RVS(%d):L fwd=%d", _id, _currentValueVariable );
#endif
          _currentValue = _currentValueVariable;
        }
        else if (_currentValueSwitch == Switch3Position::Pos2)
        {
#ifdef LOG_LOOP
          GetLog()->printf("RS(%d):L rwd=-%d", _id, _currentValueVariable);
#endif
          _currentValue = -1 * _currentValueVariable;
        }      
      }
    }
};
#endif
