//*****************************************************************
//* Class ToggleSwitch - Header
//*
//* Oscillating switch that toggles between two values. Changing the 
//* value is triggered by two signals. The class is e.g. used, to let a 
//* motor oscillate within an angle. The end positions are defined by 
//* limit switches. 
//* There are consts Pos1/Pos2 do make sketches more readable.
//* As an alternative, two monoflops can also be used.
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

#ifndef EASY_TOGGLESWTICH_H
#define EASY_TOGGLESWTICH_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

class ToggleSwitch : public Input
{
  private:
    void Init(int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec);
    
  protected:
    int _pinDirection1; // ReadOnly
    int _pinDirection2; // ReadOnly
    unsigned long _debounceTimeMSec; // ReadOnly
	ESwitchResistoreMode _switchResistoreMode;  // ReadyOnly
    byte _switchPressed= LOW; // ReadyOnly
	byte _switchNotPressed = LOW;  // ReadyOnly
    unsigned long _ignoreChangeMillis; 

  public:
 #ifdef CREATE_ID_MANUALLY  
    ToggleSwitch (int aId, int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec);
#endif	
    ToggleSwitch (int aPosition1Pin, int aPosition2Pin, ESwitchResistoreMode aSwitchResistoreMode = smPullDownInternal, int aDebounceTimeMSec = EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC);
    void Setup();
    void Loop();

   static const int Pos2 = 1;
   static const int Pos1 = 0;   
};
#endif
