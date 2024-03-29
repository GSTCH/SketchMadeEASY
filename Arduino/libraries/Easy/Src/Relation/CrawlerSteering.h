//*****************************************************************
//* Class DifferentialSteering - Header
//*
//* The steering of the two motors for a caterpillar vehicle.
//* There are two movements:
//* - Near xAxis the caterpillar makes a pivot, range is a parameter into the constructor
//* - Outside the pivot range the vehicle drives forward or backward. Steering throught diverent speeds of the two motors.
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

#ifndef EASY_CREALWERSTEARING_H
#define EASY_CREALWERSTEARING_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Relation.h"
#include "..\Kernel\Actuator.h"
#include "..\Kernel\Condition.h"
#include "..\Kernel\Input.h"
#include "..\Input\FixValue.h"

#ifndef EASY_MAX_VAUE_STEERING
#define EASY_MAX_VAUE_STEERING 1024
#endif

// Libraries
class CrawlerSteering : public Relation
{
  private:
    //*************************************
    void Init(Condition* aCondition, Actuator* aActuatorLeft, Actuator* aActuatorRight, Input* aAxisX, Input* aAxisY, int aPivotWidth)
    {
#ifdef LOG_S
      GetLog()->printf("CS(%d):C AcLId=%d, ActRId=%d, InX=%d, InY=%d, Pw=%d", _id, aActuatorLeft->GetId(), aActuatorRight->GetId(), aAxisX->GetId(), aAxisY->GetId(), aPivotWidth);
#endif
      _actuatorLeft = aActuatorLeft;
      _actuatorRight = aActuatorRight;
      _axisX = aAxisX;
      _axisY = aAxisY;
      _pivotWidth = aPivotWidth;
      
      _actuatorInputLeft = new FixValue(0, 0, EASY_MAX_VAUE_STEERING);
      _actuatorInputRight = new FixValue(0, 0, EASY_MAX_VAUE_STEERING);
      
      if (_axisX->GetMinValue() == 0 && _axisX->GetMaxValue() > 0 ) 
      {
        // support asynmetric +/- range 
        _centrePositionX = 0;
      }
      else
      {        
        _centrePositionX = (_axisX->GetMinValue() + _axisX->GetMaxValue()) / 2;       
      }
      
      if (_axisY->GetMinValue() == 0 && _axisY->GetMaxValue() > 0) 
      {
        // support asynmetric +/- range 
        _centrePositionY = 0;
      }
      else
      {        
        _centrePositionY = (_axisY->GetMinValue() + _axisY->GetMaxValue()) / 2;
      }           
    }

  protected:
    Actuator* _actuatorLeft;
    FixValue* _actuatorInputLeft;
    Actuator* _actuatorRight;
    FixValue* _actuatorInputRight;
    Input* _axisX;
    Input* _axisY;
    
    
    int _pivotWidth;
    int _centrePositionX;
    int _centrePositionY;
  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY		
    CrawlerSteering(int aId, Condition* aCondition, Actuator* aActuatorLeft, Actuator* aActuatorRight, Input* aAxisX, Input* aAxisY, int aPivotWidth)  : Relation(aId, CreateElementId(EbtRelation, EkrCompare, DIFFERENTIAL_STEARING_INDEX), aCondition)
    {
      Init(aCondition, aActuatorLeft, aActuatorRight, aAxisX, aAxisY, aPivotWidth);
    }
#endif

    //*************************************
    CrawlerSteering(Condition* aCondition, Actuator* aActuatorLeft, Actuator* aActuatorRight, Input* aAxisX, Input* aAxisY, int aPivotWidth)  : Relation(CreateElementId(EbtRelation, EkrCompare, DIFFERENTIAL_STEARING_INDEX), aCondition)
    {
      Init(aCondition, aActuatorLeft, aActuatorRight, aAxisX, aAxisY, aPivotWidth);
    }

    //*************************************
    void Loop()
    {     
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("CS(%d):L", _id);
#endif
      bool conditionChanged = false;
      
      if (_condition != NULL )
      {
        conditionChanged = _condition->CheckChanged();
        if (conditionChanged && !_condition->Check())
        {
#ifdef LOG_LOOP
          GetLog()->printf("CS(%d):L Ck=false, Sl=0, Sr=0", _id);
#endif        
          _actuatorInputLeft->SetValue(0);
          _actuatorInputRight->SetValue(0);
        
          _actuatorLeft->Act(_actuatorInputLeft);
          _actuatorRight->Act(_actuatorInputRight);               
          return;
        }
      }

      if (conditionChanged ||_axisX->ValueChanged() || _axisY->ValueChanged())
      {       
        int speedLeft = 0;
        int speedRight = 0;
        bool drive = abs(_axisY->Value() - _centrePositionY) > _pivotWidth;
        bool stop = abs(_axisX->Value() - _centrePositionX) < _pivotWidth && !drive;
        
#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("CS(%d):L Dr=%d, Y=%d, Y0=%d, MinY=%d, MaxY=%d", _id, drive, _axisY->Value(), _centrePositionY, _axisY->GetMinValue(), _axisY->GetMaxValue());
#endif     
        
        if (stop)
        {          
          // There's a stop-zone. Within the radius of the PivotWidth, the motor stops.
        }
        else if (drive)
        {         
          // Drive movement: Calc base speed from yAxis and then slowdown the steering speed in relation to xAxis
          if (_axisY->Value() > _centrePositionY)
          {
            int groundspeed = map(_axisY->Value(), _centrePositionY, _axisY->GetMaxValue(), 0, EASY_MAX_VAUE_STEERING);
            if (_axisX->Value() < _centrePositionX)
            {
              speedLeft = map(_axisX->Value(), _centrePositionX, _centrePositionX==0 ? -_axisX->GetMaxValue() : _axisX->GetMinValue(), groundspeed, 0);
              speedRight= groundspeed;
            }
            else if (_axisX->Value() > _centrePositionX)
            {
             speedLeft = groundspeed;
             speedRight= map(_axisX->Value(), _centrePositionX, _axisX->GetMaxValue(), groundspeed, 0);
            }
            else 
            {
              speedLeft = groundspeed;
              speedRight= groundspeed;
            }            
          }
          else if (_axisY->Value() < _centrePositionY)
          {
            int groundspeed = map(_axisY->Value(), _centrePositionY, _centrePositionX==0 ? -_axisY->GetMaxValue() : _axisY->GetMinValue(), 0, -EASY_MAX_VAUE_STEERING);
            if (_axisX->Value() < _centrePositionX)
            {
              speedLeft = map(_axisX->Value(), _centrePositionX, _centrePositionX==0 ? -_axisX->GetMaxValue() : _axisX->GetMinValue(), groundspeed, 0);
              speedRight= groundspeed; 
            }
            else if (_axisX->Value() > _centrePositionX)
            {              
             speedLeft = groundspeed; 
             speedRight= map(_axisX->Value(), _centrePositionX, _axisX->GetMaxValue(), groundspeed, 0);
            }
            else 
            {
              speedLeft = groundspeed;
              speedRight= groundspeed; 
            }           
          }          
        }
        else
        {
          // Pivot movement: Turn with same speed but different direction.
          if (_axisX->Value() > _centrePositionX)
          {
            speedLeft = map(_axisX->Value(), _centrePositionX, _axisX->GetMaxValue(), 0, EASY_MAX_VAUE_STEERING);
            speedRight = -speedLeft;          
          }
          else if (_axisX->Value() < _centrePositionX)
          {
            speedLeft = map(_axisX->Value(), _centrePositionX, _centrePositionX==0 ? -_axisX->GetMaxValue() : _axisX->GetMinValue(), 0, -EASY_MAX_VAUE_STEERING);
            speedRight = -speedLeft;
          }          
        }        
        
#ifdef LOG_LOOP
        GetLog()->printf("CS(%d):L Dr=%d, Sl=%d, Sr=%d", _id, drive, speedLeft, speedRight);
#endif
#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("CS(%d):L Dr=%d, Sl=%d, Sr=%d, Y=%d, Y0=%d, MinY=%d, MaxY=%d, X=%d, X0=%d", _id, drive, speedLeft, speedRight, _axisY->Value(), _centrePositionY, _axisY->GetMinValue(), _axisY->GetMaxValue(), _axisX->Value(), _centrePositionX );
#endif

        _actuatorInputLeft->SetValue(speedLeft);
        _actuatorInputRight->SetValue(speedRight);
        
        _actuatorLeft->Act(_actuatorInputLeft);
        _actuatorRight->Act(_actuatorInputRight);       
      }
    }
};
#endif
