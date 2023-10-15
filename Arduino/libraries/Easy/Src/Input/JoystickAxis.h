//*****************************************************************
//* Class JoystickAxis - Header
//*
//* Represent a joystichAxis. This is a variable (analog input) 
//* with auto calibration during startup in the middle. 
//* Value=0 is the centre position, value itself is +/-255. 
//* When moveing joystick, value changes from MINPOS to MAXPOS.
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

#ifndef EASY_JOYSTICKAXIS_H
#define EASY_JOYSTICKAXIS_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Input.h"

#ifndef CONSIDERED_MIN_CHANGE 
// To make not to much changes to the Actuators e.g. by toggleing +/-1
#define CONSIDERED_MIN_CHANGE 5 
#endif 

#ifndef DEAD_ZONE_WIDTH
// Increase the center to area of the 0 value
#define DEAD_ZONE_WIDTH 20 
#endif

class JoystickAxis : public Input
{
  protected:
    int _analogPin;
    
    int _minPos; // ReadOnly
    int _centerPos; // ReadOnly   
    int _maxPos; // ReadOnly
    bool _switchDirection; // ReadOnly
    int _deadZoneWidth; // ReadOnly
    int _consideredMinChange; // ReadOnly
	
    int _lastPos;
    int _currentPos;      
    
    unsigned long Calibrate();
    void Init(int aAnalogPin, bool aSwitchDirection, int aDeadZoneWidth, int aConsideredMinChange);

  public:
#ifdef CREATE_ID_MANUALLY    
    JoystickAxis (int aId, int aAnalogPin, bool aSwitchDirection, int aDeadZoneWidth = DEAD_ZONE_WIDTH, int aConsideredMinChange = CONSIDERED_MIN_CHANGE);
#endif	
    JoystickAxis (int aAnalogPin, bool aSwitchDirection, int aDeadZoneWidth = DEAD_ZONE_WIDTH, int aConsideredMinChange = CONSIDERED_MIN_CHANGE);
    void Setup();
    void Loop();
	
    void calibrateCentre();
    void calibrateMax();
    void calibrateMin();
};

#endif 
