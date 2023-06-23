//*****************************************************************
//* Class DigitalInput - Header
//*
//* Represent a digital input pin (e.g. sensor). Set the pin into  
//* the constructor. Optional is a debounce time (duration to ignore 
//* any changes after LOW/HIGH or HIGH/LOW change).
//* 
//* The class defines some const. They are used to write better 
//* readable conditions.
//* 
//* For a switch use Switch2Position or Switch3Position. This classes
//* know the ESwitchResistoreMode. DigitalInput defines the pin always 
//* as INPUT.
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

#ifndef DigitalIn_h
#define DigitalIn_h

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\Input.h"

class DigitalInput : public Input
{
  private:
    void Init(int aPin, int aDebounceTime);

  protected:
    int _pin; // ReadyOnly
	int _debounceTime; // ReadyOnly
    unsigned long _ignoreChangeMillis;

  public:
#ifdef CREATE_ID_MANUALLY 
    DigitalInput (int aId, int aPin, int aDebounceTime);
#endif	
    DigitalInput (int aPin, int aDebounceTime = EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC);
    void Setup();
    void Loop();

    static const int High = 1;
    static const int Low = 0;

    static const int On = 1;
    static const int Off = 0;

    static const int Pos1 = 1;
    static const int Pos0 = 0;
};

#endif
