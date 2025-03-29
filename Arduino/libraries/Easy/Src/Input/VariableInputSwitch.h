//*****************************************************************
//* Class VariableInput - Header
//*
//* Represent a combination of an analog input pin and
//* switch with three position. Typical used to control a 
//* motor with direction (switch) and motor (poti). Has the same logic 
//* as an joystick axis (switch defines the sign, variable input the amount)
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

#ifndef EASY_VARIABLEINPUTSWITCH
#define EASY_VARIABLEINPUTSWITCH

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Input.h"
#include "..\Input\Switch3Position.h"
#include "..\Input\VariableInput.h"

class VariableInputSwitch : public Input
{
  private:
    Switch3Position* _switch3Pos;
    VariableInput* _variableInput;
    
    void Init (int aAnalogPin, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime, int aConsideredMinChange)
    {
      _switch3Pos = new Switch3Position(aPosition1Pin, aPosition2Pin, aSwitchResistoreMode, aDebounceTime);
      _variableInput = new VariableInput(aAnalogPin, aConsideredMinChange); 
    }
  protected:

  public:
#ifdef CREATE_ID_MANUALLY  
    VariableInputSwitch (int aId, int aAnalogPin, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeint aConsideredMinChange);
#endif
    VariableInputSwitch (int aAnalogPin, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode ESwitchResistoreMode, int aDebounceTime, int aConsideredMinChange);
    VariableInputSwitch (int aAnalogPin, int aPosition1Pin, int aPosition2Pin);
	
    void Setup();
    void Loop();
};
#endif
