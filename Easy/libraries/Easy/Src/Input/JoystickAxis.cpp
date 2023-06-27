//*****************************************************************
//* Class JoystickAxis - Implementation
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

#include <Arduino.h>
#include "JoystickAxis.h"
#include "..\Common\Log.h"
#include <Arduino.h>
#include <Math.h>

#define IMPOSIBLE_VALUE_TO_INIT_JOYSTICKAXIS 9999
#define RESOLUTION 1024
#define CONSIDERED_MIN_CHANGE 10
#define DEATH_ZONE_WIDTH 10
#define MAX_AXIS_VALUE 255

//*************************************
#ifdef CREATE_ID_MANUALLY  
JoystickAxis::JoystickAxis (int aId, int aAnalogPin, bool aSwitchDirection) : Input(aId, CreateElementId(EbtInput, EkiAnalog, ANALOG_JOYSTICKAXIS_INDEX), 0, MAX_AXIS_VALUE)
{
  Init(aAnalogPin, aSwitchDirection);
}
#endif

//*************************************
JoystickAxis::JoystickAxis (int aAnalogPin, bool aSwitchDirection) : Input(CreateElementId(EbtInput, EkiAnalog, ANALOG_JOYSTICKAXIS_INDEX), 0, MAX_AXIS_VALUE)
{
  Init(aAnalogPin, aSwitchDirection);
}

//*************************************
void JoystickAxis::Init(int aAnalogPin, bool aSwitchDirection)
{
#ifdef LOG_SETUP
  GetLog()->printf("JA(%d):C P=%d", _id, aAnalogPin );
#endif
  _analogPin = aAnalogPin;
  _switchDirection = aSwitchDirection;

  _minPos = 0;
  _maxPos = RESOLUTION;

  _currentValue = _lastValue = IMPOSIBLE_VALUE_TO_INIT_JOYSTICKAXIS;
  _currentPos = _lastPos = IMPOSIBLE_VALUE_TO_INIT_JOYSTICKAXIS;
}

//*************************************
void JoystickAxis::Setup()
{
  calibrateCentre();
}

//*************************************
void JoystickAxis::Loop()
{
  _lastPos = _currentPos;
  _lastValue = _currentValue;

  int readValue = analogRead(_analogPin);
#ifdef LOG_DEBUG
  GetLog()->printf("JA(%d):L Vl=%d", _id, readValue);
#endif

  if (abs(readValue - _lastPos) > CONSIDERED_MIN_CHANGE)
  {
    if (abs(readValue - _centerPos) < DEATH_ZONE_WIDTH)
    {
      _currentPos =  _centerPos;
      _currentValue = 0;
    }
    else if (_currentPos > _centerPos)
    {
      _currentPos = readValue;
      if (_switchDirection)
      {
#ifdef LOG_DEBUG
        GetLog()->printf("JA(%d):L Mp1=%d [%d, %d][%d, %d]", _id, _currentPos - _centerPos, 0, _maxPos - _centerPos, 0, MAX_AXIS_VALUE);
#endif
        _currentValue = -map(_currentPos - _centerPos, 0, _maxPos - _centerPos, 0, MAX_AXIS_VALUE );
      }
      else
      {
#ifdef LOG_DEBUG
        GetLog()->printf("JA(%d):L Mp2=%d [%d, %d][%d, %d]", _id, _currentPos - _centerPos, 0, _maxPos - _centerPos, 0, MAX_AXIS_VALUE);
#endif
        _currentValue = map(_currentPos - _centerPos, 0, _maxPos - _centerPos, 0, MAX_AXIS_VALUE );
      }
    }
    else if (_currentPos < _centerPos)
    {
      _currentPos = readValue;
      if (_switchDirection)
      {
#ifdef LOG_DEBUG
        GetLog()->printf("JA(%d):L Mp3=%d [%d, %d][%d, %d]", _id, _centerPos - _currentPos, 0, _centerPos, 0, MAX_AXIS_VALUE);
#endif
        _currentValue = map(_centerPos - _currentPos, 0, _centerPos, 0, MAX_AXIS_VALUE );
      }
      else
      {
#ifdef LOG_DEBUG
        GetLog()->printf("JA(%d):L Mp4=%d [%d, %d][%d, %d]", _centerPos - _currentPos, 0, _centerPos, 0, MAX_AXIS_VALUE);
#endif
        _currentValue = -map(_centerPos - _currentPos, 0, _centerPos, 0, MAX_AXIS_VALUE );
      }

      if (_currentValue > _maxValue)
      {
        _currentValue = _maxValue;
      }
      else if (_currentValue < -_maxValue)
      {
        _currentValue = -_maxValue;
      }
    }
    else
    {
      if (_switchDirection)
      {
        _currentPos = readValue;
      }
      else
      {
        _currentPos = -readValue;
      }
    }

#ifdef LOG
    GetLog()->printf("JA(%d):L Vl=%d consider (CPs=%d, LPs=%d)", _id, _currentValue, _currentPos, _lastPos);
#endif
  }
  else
  {
#ifdef LOG_DEBUG
    GetLog()->printf("JA(%d):L LVl=%d, Vl=%d ignored", _id, _lastValue, readValue);
#endif
  }
}

//*************************************
unsigned long JoystickAxis::Calibrate()
{
  unsigned long calibrate = 0;
  for (int i = 0; i <= 100; ++i)
  {
    calibrate += analogRead(_analogPin);
    // The value has a Jitter. To get the middle value, we hat to wait a little before reading the next value.
    // Delay is in this case allowed because it's in Setup().
    delay(20);
  }

  // Integer division rounds itselfs
  return calibrate / 100;
}

//*************************************
void JoystickAxis::calibrateCentre()
{
  _centerPos = Calibrate();

#ifdef LOG
  GetLog()->printf("JA(%d):Ca Ctr=%d", _id, _centerPos);
#endif

}

//*************************************
void JoystickAxis::calibrateMax()
{
  _maxPos = Calibrate();

#ifdef LOG
  GetLog()->printf("JA(%d):Ca Max=%d", _id, _maxPos);
#endif
}

//*************************************
void JoystickAxis::calibrateMin()
{
  _minPos = Calibrate();

#ifdef LOG
  GetLog()->printf("JA(%d):Ca Min=%d", _id, _minPos);
#endif
}
