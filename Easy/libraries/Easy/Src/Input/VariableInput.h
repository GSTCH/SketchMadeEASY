//*****************************************************************
//* Class VariableInput - Header
//*
//* Represent an analog input pin
//*
//* 
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

#ifndef EASY_VARIABLEINPUT_H
#define EASY_VARIABLEINPUT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Input.h"

#define EASY_VARIABLEINPUT_CONSIDERED_MIN_CHANGE 5

class VariableInput : public Input
{
  private:
    void Init (int aAnalogPin, int aConsideredMinChange);
  protected:
    int _analogPin;
	int _consideredMinChange;
  public:
#ifdef CREATE_ID_MANUALLY  
    VariableInput (int aId, int aAnalogPin, int aConsideredMinChange);
#endif
    VariableInput (int aAnalogPin, int aConsideredMinChange = EASY_VARIABLEINPUT_CONSIDERED_MIN_CHANGE);
	
    void Loop();
};

#endif
