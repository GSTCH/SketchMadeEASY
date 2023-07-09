//*****************************************************************
//* Class ServoBase - Header
//*
//* Servo logic base class (angle controlled moving)
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#ifndef EASY_SERVBOBASE_H
#define EASY_SERVBOBASE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "Actuator.h"
#include "ServoShieldBase.h"

class ServoBase : public Actuator
{
  private:
    int _minAngle;
    int _maxAngle;
    int _currentAngle;

  protected:
    ServoShieldBase* _servoShield;

  public:
 #ifdef CREATE_ID_MANUALLY    
    ServoBase (int aId, int aMinAngle, int aMaxAngle, struct SElementType aElementType);
#endif	
    ServoBase (int aMinAngle, int aMaxAngle, struct SElementType aElementType);
    void Setup();
    void Loop();
    void Act(Input* aInput);
    void angle(int aAngle);
	
	inline int getMinAngle(){
		return _minAngle;
	}
	
	inline int getMaxAngle(){
		return _maxAngle;
	}
};

#endif
