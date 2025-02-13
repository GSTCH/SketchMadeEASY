//*****************************************************************
//* Class EyeControl - Header
//*
//* Calc driven by an IteratorValue the random XYposition to simulate 
//* an eye. IteratorValue is the master and X-direction, when the 
//* direction changes, the logic calc a random Y-max value and moves 
//* during X move to this position. MaxY is when X is in the middle 
//* position.
//*           ^
//*           |
//*  <----- PulseGenerator ---->   
//*           |
//*           v
//*
//*  Primary movement:    MinX  ... MidX        ... MaxX
//*  Secondary movement:  Y=0   ... Y_randomMax ... Y=0
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

#ifndef EASY_EYECONTROL_H
#define EASY_EYECONTROL_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Relation.h"
#include "..\Kernel\Actuator.h"
#include "..\Kernel\Condition.h"
#include "..\Kernel\Input.h"
#include "..\Input\FixValue.h"

#define MECHANICAL_TOLERANCE 30

class EyeControl : public Relation
{
  private:
   //*************************************
   Input* _pulseGenerator;
   FixValue* _yAxisInput;
   ServoBase* _xActuator;
   ServoBase* _yActuator;
   int _xValue;
   float _yValue;
   float _stepWidthY;
   int _stepCount;
   int _midX;
   int _midY;
	int _yRangeMin;
	int _yRangeMax;
   bool _directionIncreasing;
  
   void Init(Input* aPulseGenerator, ServoBase* aX, ServoBase* aY)
   {
    _pulseGenerator = aPulseGenerator;
  
    _midY = (aY->getMinAngle() + aY->getMaxAngle()) / 2;
    _yAxisInput = new FixValue(_midY, aY->getMinAngle(), aY->getMaxAngle());
  	 _yRangeMin = (int)(_yAxisInput->GetMinValue() * 0.8); 
	 _yRangeMax = (int)(_yAxisInput->GetMaxValue() * 0.8);

    _xActuator  = aX;
    _yActuator = aY;  
   
    _yValue = _midY;
    _stepCount = 0;
    _stepWidthY  = 0;
    _directionIncreasing = false;
    _midX = (_pulseGenerator->GetMaxValue() + _pulseGenerator->GetMinValue()) / 2;
    _xValue = _pulseGenerator->Value();
  
    // Init random generator
    randomSeed(241967);
  
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("EY(%d):S X (%d, %d, %d)", _id, _pulseGenerator->GetMinValue(), _midX, _pulseGenerator->GetMaxValue());
    GetLog()->printf("EY(%d):S Y (%d, %d, %d)", _id, aY->getMinAngle(), _midY, aY->getMaxAngle());
#endif   
  }
  
  public:
#ifdef CREATE_ID_MANUALLY   
   //*************************************
   EyeControl(int aId, Condition* aCondition, Input* aPulseGenerator, ServoBase* aX, ServoBase* aY)
   : Relation(aId, CreateElementId(EbtRelation, EkrCompare, EYECONTROL_INDEX), aCondition)
   {
    Init(aPulseGenerator, aX, aY);
   }  
#endif  

   //*************************************
   EyeControl(Condition* aCondition, Input* aPulseGenerator, ServoBase* aX, ServoBase* aY)
   : Relation(CreateElementId(EbtRelation, EkrCompare, EYECONTROL_INDEX), aCondition)
   {
    Init(aPulseGenerator, aX, aY);
   }
  
   //*************************************
   void Loop()
   {    
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("EY(%d):L", _id);
#endif

    if (_condition != NULL && !_condition->Check())    
    {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("EY(%d):L Cnd=0", _id);
#endif		

	  // Assigned condition is false, nothing to do
      return;
    }

    if (_xValue == _pulseGenerator->Value())
    {
      // Do anything if xValue changed, else it's a non blocking sleep
      return;
    } 
    
    _xValue = _pulseGenerator->Value();
  
    bool doesDirectionChanges = false;
    if (_stepCount > 0 )      
    {    
      doesDirectionChanges = (_directionIncreasing && (_pulseGenerator->Value() < _pulseGenerator->GetLastValue())) || 
                     (!_directionIncreasing && (_pulseGenerator->Value() > _pulseGenerator->GetLastValue()));  
    }
    else
    {
      _directionIncreasing = _pulseGenerator->Value() > _pulseGenerator->GetLastValue();
   
      // direction changes, calculate the new Y-max. 
      int stepWidth = abs(_pulseGenerator->Value() - _pulseGenerator->GetLastValue());
      if (stepWidth>0)
      {
       _stepCount = (_pulseGenerator->GetMaxValue() - _pulseGenerator->GetMinValue()) / (2 * stepWidth);
       doesDirectionChanges = true;
      }
   
#ifdef LOG_LOOP
      GetLog()->printf("EY(%d):L Sc=%d, Sw=%d, Dir=%d", _id, _stepCount, stepWidth, _directionIncreasing);
#endif       
    }

    if (doesDirectionChanges)
    {   
      long nextMaxY = (int)(random(_yAxisInput->GetMinValue(), _yAxisInput->GetMaxValue()));
      _stepWidthY = 1.967 * (nextMaxY - _midY) / _stepCount;
      _yValue = _midY;
      _directionIncreasing = !_directionIncreasing;
   
#ifdef LOG_LOOP
      GetLog()->printf("EY(%d):L SW=%d, NxMaxY=%d, YVal=%d", _id, (int)_stepWidthY, nextMaxY, (int)_yValue);
#endif  
    }
    else
    {   
      if (_pulseGenerator->Value() > _midX)
      {  
       if (_directionIncreasing)   
       {
        _yValue += _stepWidthY;
       }
       else
       {
        _yValue -= _stepWidthY;  
       }
#ifdef LOG_LOOP
      GetLog()->printf("EY(%d):L+ I=%d, XVal=%d, YVal=%d", _id, _directionIncreasing, _pulseGenerator->Value(), (int)_yValue);
#endif   
      }
      else if (_pulseGenerator->Value() < _midX)
      {
       if (_directionIncreasing)   
       {
        _yValue -= _stepWidthY;
       }
       else
       {
        _yValue += _stepWidthY;
       }
#ifdef LOG_LOOP
       GetLog()->printf("EY(%d):L- I=%d, XVal=%d, YVal=%d", _id, _directionIncreasing, _pulseGenerator->Value(), (int)_yValue);
#endif      
      }  
    }
  
    int  borderDistance = 0;
    if (_pulseGenerator->Value() > _midX)
    {
      borderDistance = _pulseGenerator->GetMaxValue() - _pulseGenerator->Value();
    }
    else
    {
      borderDistance = _pulseGenerator->Value() - _pulseGenerator->GetMinValue();
    }
  
    if (borderDistance < MECHANICAL_TOLERANCE)
    {
#ifdef LOG_LOOP
      GetLog()->printf("EY(%d):L BD=%d", _id, borderDistance);
#endif
    
      // At the end position of the eyes, we protect the mechanic and make sure 
      // that the eye is in a horicontal middle position.
      _yValue = _midY;
    }
  
    // Calculate the positions by mapping the value
	if (_yValue > _yRangeMin && _yValue < _yRangeMax )
    {
	 _yAxisInput->SetValue(_yValue);
	}
#ifdef LOG_LOOP_DEBUG	
	else
	{
      GetLog()->printf("EY(%d):L Ltd %d %d %d", _id, _yValue, _yRangeMin, _yRangeMax );		
	}
#endif	
    _yActuator->Act(_yAxisInput);	 
  
    _xActuator->Act(_pulseGenerator);
   }  
};
#endif
