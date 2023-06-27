//*****************************************************************
//* Class VariableOutput - Header
//*
//* Represent an analog output pin (PWM). Check board type to know 
//* the PINs able to make an analog/PWM signal.
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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

#ifndef EASY_VARIABLEOUTPUT_H
#define EASY_VARIABLEOUTPUT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Actuator.h"
#include "..\Kernel\Input.h"

#define ON 1
#define OFF 0
#define IMPOSIBLE_VALUE_TO_INIT_VARIABLEOUTPUT 999
#define DIGITALOUTPUT_MINVALUE 0
#define DIGITALOUTPUT_MAXVALUE 255

class VariableOutput : public Actuator
{
  private:
    //*************************************
    void Init(int aPwmPin)
    {
#ifdef LOG_SETUP
      GetLog()->printf("VO(%d):C P=%d", _id, aPwmPin );
#endif
      _pwmPin = aPwmPin;
      _currentValue = IMPOSIBLE_VALUE_TO_INIT_VARIABLEOUTPUT;
    }

  protected:
    int _pwmPin;
    int _currentValue;

  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY 	
    VariableOutput (int aId, int aPwmPin) : Actuator(aId, CreateElementId(EbtActuator, EkaAnalog, ANALOG_OUTPUT_INDEX))
    {
      Init(aPwmPin);
    }
#endif

    //*************************************
    VariableOutput (int aPwmPin) : Actuator(CreateElementId(EbtActuator, EkaAnalog, ANALOG_OUTPUT_INDEX))
    {
      Init(aPwmPin);
    }

    //*************************************
    void Setup()
    {
#ifdef LOG_SETUP
      GetLog()->printf("VO(%d):S", _id );
#endif

      pinMode(_pwmPin, OUTPUT);
    }

    //*************************************
    void Act(Input* aInput)
    {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("VO(%d):A Value=%d, CV=%d, Min=%d, Max=%d", _id, aInput->Value(),  _currentValue, aInput->GetMinValue(), aInput->GetMaxValue() );
#endif

      if (aInput->Value() != _currentValue)
      {       
        _currentValue = aInput->Map(DIGITALOUTPUT_MINVALUE, DIGITALOUTPUT_MAXVALUE);
        analogWrite(_pwmPin, _currentValue);

#ifdef LOG_LOOP
        GetLog()->printf("VO(%d):A CVl=%d", _id, _currentValue );
#endif
      }
    }
};
#endif
