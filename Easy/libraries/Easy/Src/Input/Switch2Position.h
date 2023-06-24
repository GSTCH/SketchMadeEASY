//*****************************************************************
//* Class Switch2Position - Header
//*
//* Switch with two position. Use one diginal in pin set in the 
//* constructor. Optional is a debounce time (duration to ignore 
//* any changes after LOW/HIGH or HIGH/LOW change).
//* This classes support the ESwitchResistoreMode, set in the 
//* constructor. Default is internal pullup. 
//*
//* The class defines some const. They are used to write better 
//* readable conditions.
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#ifndef EASY_SWITCH2POSITION_H
#define EASY_SWITCH2POSITION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\Input.h"

class Switch2Position : public Input
{
  private:
    void Init(int aPosition1Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime);
  protected:
    int _position1Pin;  // ReadyOnly
    ESwitchResistoreMode _switchResistoreMode;  // ReadyOnly
	int _debounceTime; // ReadyOnly
    byte switchValue[2] {LOW, LOW}; // ReadyOnly

    unsigned long _ignoreChangeMillis;
  public:
 #ifdef CREATE_ID_MANUALLY  
    Switch2Position (int aId, int aPosition1Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTime);
#endif	
    Switch2Position (int aPosition1Pin, ESwitchResistoreMode aSwitchResistoreMode = smPullDownInternal, int aDebounceTime = EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC);
	
    void Setup();
    void Loop();

    static const int Pos1 = 1;
    static const int Pos0 = 0;
    static const int On = 1;
    static const int Off = 0;
};

#endif
