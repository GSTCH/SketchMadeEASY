//*****************************************************************
//* Class UltrasonicRangefinder - Header
//*
//* A common Ultrasonic Rangefinders such as the HY-SRF05
//* Value (distance in [cm]).
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

#ifndef EASY_ULTRASONICRANGEFINDER_H
#define EASY_ULTRASONICRANGEFINDER_H

#ifdef USE_NEWPING
  #include <NewPing.h>
#else
  #include <Arduino.h>
  #ifndef EASY_MEASURE_REPETITIONS
    #define EASY_MEASURE_REPETITIONS 1
  #endif
#endif
#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Input.h"
#include "..\Common\Log.h"

#ifndef EASY_MAX_DISTANCE
#define EASY_MAX_DISTANCE 200
#endif

#ifndef EASY_MEASURE_INTERVAL_MSEC
#define EASY_MEASURE_INTERVAL_MSEC 500
#endif

#ifndef EASY_MINIMUM_MEASURE_INTERVAL_MSEC
// Sensor does not work when read to often
#define EASY_MINIMUM_MEASURE_INTERVAL_MSEC 100
#endif

class UltrasonicRangefinder : public Input {
private:
#ifdef USE_NEWPING
  NewPing* _ultraSonic;
#endif

  //*************************************
  void Init(int aEchoPin, int aTriggerPin, int aMeasureInterval = EASY_MEASURE_INTERVAL_MSEC) {
#ifdef LOG_SETUP
    GetLog()->printf("UR(%d):C EP=%d, TP=%d MI=%d", _id, aEchoPin, aTriggerPin, aMeasureInterval);
#endif

    _echoPin = aEchoPin;
    _triggerPin = aTriggerPin;
    if (aMeasureInterval > EASY_MINIMUM_MEASURE_INTERVAL_MSEC) {
      _measureInterval = aMeasureInterval;
    } else {      
      _measureInterval = EASY_MINIMUM_MEASURE_INTERVAL_MSEC;
    }

#ifdef USE_NEWPING
    _ultraSonic = new NewPing(_triggerPin, _echoPin, EASY_MAX_DISTANCE);
#endif
  }

  unsigned long MessureOneTime() {
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    // Measure duration
    return pulseIn(_echoPin, HIGH);
  }

protected:
  int _echoPin;
  int _triggerPin;
  int _measureInterval;
  unsigned long _lastMeasure;

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY 
  UltrasonicRangefinder(int aId, int aEchoPin, int aTriggerPin, int aMeasureInterval)
    : Input(aId, CreateElementId(EbtInput, EkiSensor, SENSOR_ULTRASONICRANGEFINDER_INDEX), 0, EASY_MAX_DISTANCE) {
    Init(aEchoPin, aTriggerPin, aMeasureInterval);
  }
#endif

  //*************************************
  UltrasonicRangefinder(int aEchoPin, int aTriggerPin, int aMeasureInterval)
    : Input(CreateElementId(EbtInput, EkiSensor, SENSOR_ULTRASONICRANGEFINDER_INDEX), 0, EASY_MAX_DISTANCE) {
    Init(aEchoPin, aTriggerPin, aMeasureInterval);
  }

  //*************************************
  UltrasonicRangefinder(int aEchoPin, int aTriggerPin, int aMeasureInterval, int aMinValue, int aMaxValue)
    : Input(CreateElementId(EbtInput, EkiSensor, SENSOR_ULTRASONICRANGEFINDER_INDEX), aMinValue, aMaxValue) {
    Init(aEchoPin, aTriggerPin, aMeasureInterval);
  }

  //*************************************
  void Setup() {
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    _lastMeasure = millis();
  }

  //*************************************
  void Loop() {
    unsigned long current_time = millis();

    if ((current_time - _lastMeasure) < _measureInterval) {
#ifdef LOG_LOOP_DEBUG
      unsigned long rest = _measureInterval - (current_time - _lastMeasure);
      GetLog()->printf("UR(%d):L R=%u", _id, rest);
#endif
      return;
    }

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("UR(%d):L Start measure", _id);
#endif

    // Measure the distance because period time has been expired
    _lastValue = _currentValue;

    unsigned long duration = 0;
#ifdef USE_NEWPING
    duration = _ultraSonic->ping();
#else
    // Init measuring for a better distance we repeat it.
    for (int idx = 0; idx < EASY_MEASURE_REPETITIONS; ++idx) {
      duration += MessureOneTime();
      if (idx < EASY_MEASURE_REPETITIONS-1) {
        // TODO: Improve with a non blocking sleep
        delay(EASY_MINIMUM_MEASURE_INTERVAL_MSEC);
      }
    }
    duration /= EASY_MEASURE_REPETITIONS;

#endif

    // Calc lenth in [cm]:
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the object we
    // take half of the distance travelled.
    _currentValue = duration / (29 * 2.0);  // Integer division, floors value

#ifdef LOG_LOOP
    if (_lastValue!=_currentValue)
    {
	  GetLog()->printf("UR(%d):L CVl=%d", _id, _currentValue);
    }
#endif

    _lastMeasure = current_time;
  }
};

#endif
