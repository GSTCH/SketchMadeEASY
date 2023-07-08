//*****************************************************************
//* Class JoystickAxis - Header
//*
//* Represent two joystichAxis. This is a variable (analog input) 
//* with auto calibration during startup. Value=0 is the centre 
//* position, value itself is +/-255. When moveing joystick, value changes from MINPOS 
//* to MAXPOS.
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

#ifndef EASY_JOYSTICKAXIS_H
#define EASY_JOYSTICKAXIS_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Input.h"

class JoystickAxis : public Input
{
  protected:
    int _analogPin;
    
    int _minPos; // ReadOnly
    int _centerPos; // ReadOnly   
    int _maxPos; // ReadOnly
    bool _switchDirection; // ReadOnly
	
    int _lastPos;
    int _currentPos;      
    
    unsigned long Calibrate();
    void Init(int aAnalogPin, bool aSwitchDirection);

  public:
#ifdef CREATE_ID_MANUALLY    
    JoystickAxis (int aId, int aAnalogPin, bool aSwitchDirection);
#endif	
    JoystickAxis (int aAnalogPin, bool aSwitchDirection);
    void Setup();
    void Loop();
	
    void calibrateCentre();
    void calibrateMax();
    void calibrateMin();
};

#endif 
