//*****************************************************************
//* Class Monoflop - Header
//*
//* Defined duration of the signal. The duration of high and low can be configured
//* LowDelay and HighDelay has to be greather than debounce time.
//*
//* Values: 0=Low             - Detect pin value change to low (one cycle)
//*         1=LowTimerRuns    - Low timer runs
//*         2=LowTimerEnd     - Low delay ended (value remain until pin value changes)
//*
//*         3=High            - Detect pin value change to high (one cycle)
//*         4=High timer runs - High delay runs
//*         5=High timer end  - High delay ended (value remain until pin value changes)
//*
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

#ifndef EASY_MONOFLOP_H
#define EASY_MONOFLOP_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\Input.h"

enum MonoflopState { 
       mfStateLow=0, mfStateLowTimerRun=1,mfStateLowTimerEnd=2, 
       mfStateHigh=3, mfStateHighTimerRun=4, mfStateHighTimerEnd=5 };  


class MonoFlop : public Input
{
  private:
    bool _autoStartup; // Flag to start timer during startup (depending on pin value)
    unsigned long _debounceTimeMSec; // ReadOnly
    byte _switchPressed; // ReadyOnly, consider SwitchResistorMode
    byte _switchNotPressed; // ReadyOnly, consider SwitchResistorMode
    ESwitchResistoreMode _switchResistoreMode; // ReadyOnly
    unsigned long _monoflopEndTime;
    unsigned long _ignoreChangeMillis;

    void Init(int aPin, int aHighDelay, int aLowDelay, bool aStart, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec);

  protected:
    int _pin; // ReadyOnly
    int _highDelay; // ReadyOnly
    int _lowDelay; // ReadyOnly
	
    int _currentPinValue;
    int _lastPinValue;

  public:
#ifdef CREATE_ID_MANUALLY   
    MonoFlop(int aId, int aPin, int aHighDelay, int aLowDelay, bool aStart, ESwitchResistoreMode aSwitchResistoreMode, int aDebounceTimeMSec);
#endif	

    MonoFlop(int aPin, int aHighDelay, int aLowDelay, bool aStart, ESwitchResistoreMode aSwitchResistoreMode = smPullDownInternal, int aDebounceTimeMSec = EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC);
	
    void Setup();
	
    void Loop();
	
	const static int StateLow = mfStateLow;
	const static int StateLowTimerRun = mfStateLowTimerRun;
	const static int StateLowTimerEnd = mfStateLowTimerEnd;
	const static int StateHigh = mfStateHigh;
	const static int StateHighTimerRun = mfStateHighTimerRun;
	const static int StateHighTimerEnd = mfStateHighTimerEnd;
};
#endif
