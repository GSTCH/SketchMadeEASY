//*****************************************************************
//* Class DifferentialSteering - Header
//*
//* The steering of the two wheels works in the same way as a caterpillar vehicle.
//* The library "DifferentialSteering" (https://github.com/edumardo/DifferentialSteering) is used.
//* This is available as a library for download in the IDE.
//*
//* For a technical description and documentation of the algorithm, see
//* https://www.impulseadventure.com/elec/robot-differential-steering.html
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
#define EASY_MAX_VAUE_STEERING 127
#endif

// Libraries
#include <DifferentialSteering.h> // https://github.com/edumardo/DifferentialSteering

class CrawlerSteering : public Relation
{
  private:
    DifferentialSteering* Steering;

    //*************************************
    void Init(Condition* aCondition, Actuator* aActuatorLeft, Actuator* aActuatorRight, Input* aAxisX, Input* aAxisY)
    {
#ifdef LOG_S
      GetLog()->printf("CS(%d):C AcLId=%d, ActRId=%d, InX=%d, InY=%d", _id, aActuatorLeft->GetId(), aActuatorRight->GetId(), aAxisX->GetId(), aAxisY->GetId());
#endif
      _actuatorLeft = aActuatorLeft;
      _actuatorRight = aActuatorRight;
      _axisX = aAxisX;
      _axisY = aAxisY;

      Steering = new DifferentialSteering();
      Steering->begin(EASY_MAX_VAUE_STEERING);

      _actuatorInputLeft = new FixValue(0, -EASY_MAX_VAUE_STEERING, EASY_MAX_VAUE_STEERING);
      _actuatorInputLeft->SetValue(0);

      _actuatorInputRight = new FixValue(0, -EASY_MAX_VAUE_STEERING, EASY_MAX_VAUE_STEERING);
      _actuatorInputRight->SetValue(0);
    }

  protected:
    Actuator* _actuatorLeft;
    FixValue* _actuatorInputLeft;
    Actuator* _actuatorRight;
    FixValue* _actuatorInputRight;

    Input* _axisX;
    Input* _axisY;

  public:
    //*************************************
#ifdef CREATE_ID_MANUALLY		
    CrawlerSteering(int aId, Condition* aCondition, Actuator* aActuatorLeft, Actuator* aActuatorRight, Input* aAxisX, Input* aAxisY)  : Relation(aId, CreateElementId(EbtRelation, EkrCompare, DIFFERENTIAL_STEARING_INDEX), aCondition)
    {
      Init(aCondition, aActuatorLeft, aActuatorRight, aAxisX, aAxisY);
    }
#endif

    //*************************************
    CrawlerSteering(Condition* aCondition, Actuator* aActuatorLeft, Actuator* aActuatorRight, Input* aAxisX, Input* aAxisY)  : Relation(CreateElementId(EbtRelation, EkrCompare, DIFFERENTIAL_STEARING_INDEX), aCondition)
    {
      Init(aCondition, aActuatorLeft, aActuatorRight, aAxisX, aAxisY);
    }

    //*************************************
    void Loop()
    {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("CS(%d):L", _id);
#endif

      if ((_condition->Check() && _condition->CheckChanged()) || ((_axisX->ValueChanged() || _axisY->ValueChanged()) && _condition->Check()))
      {
        int xMapped = 0;
        if (_axisX->Value() > 0)
        {
          xMapped = map(_axisX->Value(), 0, _axisX->GetMaxValue(), 0, EASY_MAX_VAUE_STEERING);
          if (xMapped > EASY_MAX_VAUE_STEERING)
          {
            xMapped = EASY_MAX_VAUE_STEERING;
          }
        }
        else if (_axisX->Value() < 0)
        {
          xMapped = map(_axisX->Value(),  _axisX->GetMinValue(), 0, -EASY_MAX_VAUE_STEERING, 0);
          if (xMapped < -EASY_MAX_VAUE_STEERING)
          {
            xMapped = -EASY_MAX_VAUE_STEERING;
          }
        }

        int yMapped = 0;
        if (_axisY->Value() > 0)
        {
          yMapped = map(_axisY->Value(), 0, _axisY->GetMaxValue(), 0, EASY_MAX_VAUE_STEERING);
          if (yMapped > EASY_MAX_VAUE_STEERING)
          {
            yMapped = EASY_MAX_VAUE_STEERING;
          }
        }
        else if (_axisY->Value() < 0)
        {
          yMapped = map(_axisY->Value(),  _axisY->GetMinValue(), 0, -EASY_MAX_VAUE_STEERING, 0);
          if (yMapped < -EASY_MAX_VAUE_STEERING)
          {
            yMapped = -EASY_MAX_VAUE_STEERING;
          }
        }


#ifdef LOG_LOOP
        GetLog()->printf("CS(%d):L Ck=%d X=%d XMp=%d, Y=%d, YMp=%d", _id, _condition->Check(), xMapped, _axisX->Value(), yMapped, _axisY->Value());
#endif

        // Calculate new speeds
        Steering->computeMotors(xMapped, yMapped);

        _actuatorInputLeft->SetValue(Steering->computedLeftMotor());
        _actuatorInputRight->SetValue(Steering->computedRightMotor());

        _actuatorLeft->Act(_actuatorInputLeft);
        _actuatorRight->Act(_actuatorInputRight);
      }
    }
};
#endif
