//*****************************************************************
//* Class DigitalOutput - Header
//*
//* Digital output (e.g. relais, lamp, led, ...)
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

#ifndef EASY_DIGITALOUTPUT_H
#define EASY_DIGITALOUTPUT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Actuator.h"
#include "..\Kernel\Input.h"

class DigitalOutput : public Actuator
{
  private:
    //*************************************
    void Init(int aPin)
    {
#ifdef LOG_SETUP
      GetLog()->printf("DO(%d):C P=%d", _id, aPin );
#endif
      _digitalOutPin = aPin;
      _currentValue = false;
    }

  protected:
    int _digitalOutPin;
    bool _currentValue;

  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY 	
    DigitalOutput (int aId, int aPin) : Actuator(aId, CreateElementId(EbtActuator, EkaDigital, DIGITAL_OUTPUT_INDEX))
    {
      Init(aPin);
    }
#endif

    //*************************************
    DigitalOutput(int aPin) : Actuator(CreateElementId(EbtActuator, EkaDigital, DIGITAL_OUTPUT_INDEX))
    {
      Init(aPin);
    }

    //*************************************
    void Setup()
    {
#ifdef LOG_SETUP
      GetLog()->printf("DO(%d):S", _id );
#endif

      pinMode(_digitalOutPin, OUTPUT);
    }

    //*************************************
    void Act(Input* aInput)
    {
      if (aInput->Value() > 0 && !_currentValue)
      {
        _currentValue = true;
        digitalWrite(_digitalOutPin, HIGH);
#ifdef LOG_LOOP
      GetLog()->printf("DO(%d):A Vl=1", _id );
#endif
      }
      else if (aInput->Value() <= 0 && _currentValue)
      {
        _currentValue = false;
        digitalWrite(_digitalOutPin, LOW);
#ifdef LOG_LOOP
      GetLog()->printf("DO(%d):A Vl=0", _id );
#endif
      }
    }
    
    static const int High = 1;
    static const int Low = 0;

    static const int Pos0=0;
    static const int Pos1=1;
    
    static const int Off=0;
    static const int On=1;
};
#endif
