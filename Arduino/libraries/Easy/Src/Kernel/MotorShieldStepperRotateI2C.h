//*****************************************************************
//* Class StepperPosition - Header
//*
//* Internal class to set command of a stepper with controlled by
//* Adafruit Motor Shield V2, with controled rotation.
//*
//* Adafruit Motor Shield V2 library only supports rotate by angle. 
//* "Exact RPM" is not supported. AccelStepper does not support this either.
//* Long angle presets are not allowed because it blocks the sketch. 
//* This solution only blocks the sketch during each step. Due to the 
//* many small steps during the loop, there is enough time to process 
//* the events.
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

#ifndef EASY_MOTORSHIELDSTEPPERROTATEI2C_H
#define EASY_MOTORSHIELDSTEPPERROTATEI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"

#ifndef STEPPERROTATE_I2C_MAX_CYCLES_PER_SEC
// 1000 PPS/sec (according to manufacturer)
#define STEPPERROTATE_I2C_MAX_CYCLES_PER_SEC 1000 // 17
#endif


class MotorShieldStepperRotateI2C : public MotorShieldBase {
private:
  Adafruit_MotorShield* _shield;
  Adafruit_StepperMotor* _stepper;
  int _resolution;
  int _direction;
  EStepStyle _stepStyle;
  unsigned long _lastLoopTime;
  int _cycleSpeed;
  int _maxCylcesPerSecond;

public:
  //*************************************
  //* aStepperNr : Number of stepper on shield
  //* aResolution : steps per revolution of the stepper motor (without gear) [PPS]
  //* aMaxCylcesPerSecond : Max frequency of the stepper motor [PPS]
  //* aStepStyle : Type of stepper motor signal (ssSingle, ssDouble, ssInterleave, ssMicrostep)
  //* aBusAdddress : I2C Address of the shield
  MotorShieldStepperRotateI2C(int aStepperNr, int aResolution, int aMaxCylcesPerSecond = STEPPERROTATE_I2C_MAX_CYCLES_PER_SEC, EStepStyle aStepStyle = ssSingle, int aBusAdddress = 0x60)
    : MotorShieldBase() {
#ifdef LOG_SETUP
    GetLog()->printf("SRI:C N=%d, R=%d, M=%d, A=%d", aStepperNr, aResolution, aMaxCylcesPerSecond, aBusAdddress);
#endif
    _resolution = aResolution;
    _direction = 0;
    _cycleSpeed = 0;
    _stepStyle = aStepStyle;
    _maxCylcesPerSecond = aMaxCylcesPerSecond;
    _lastLoopTime = 0;

    _minMotorShieldSpeed = 0;
    _maxMotorShieldSpeed = round(1.0 * aMaxCylcesPerSecond / aResolution * 60);
#ifdef LOG_SETUP
    GetLog()->printf("SRI:C Vmax=%d", _maxMotorShieldSpeed);
#endif

    if (aStepperNr > 2 || aStepperNr < 1) {
#ifdef LOG_SETUP
      GetLog()->printf("SRI:C MNr %d to 1", aStepperNr);
#endif
      aStepperNr = 1;
    }
    _shield = AdafruitI2cShield::getMotorShield(aBusAdddress);

    if (_shield == NULL) {
#ifdef LOG_SETUP
      GetLog()->printf("SRI:C No shdObj");
#endif
      return;
    }

    _stepper = _shield->getStepper(aResolution, aStepperNr);
    if (_stepper == NULL) {
#ifdef LOG_SETUP
      GetLog()->printf("MA(Mo=%d):S No motObj");
#endif
    }
  }

  //*************************************
  void Setup() {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("SRI:S");
#endif
    if (!_shield->begin()) {
      // create with the default frequency 1.6KHz
#ifdef LOG_SETUP
      GetLog()->printf("SPR:S Motor shield wiring!?");
#endif
    }
  }

  //*************************************
  void Loop() {
    unsigned long currentTime = millis();
    int cyclesToGo = 0;
    if (_lastLoopTime > 0) {
      cyclesToGo = (currentTime - _lastLoopTime) / 1000.0 * _cycleSpeed;

      int maxStepsPerLoop = _maxCylcesPerSecond >> 4;
      if (cyclesToGo > maxStepsPerLoop) {
        cyclesToGo = maxStepsPerLoop;
      }
    } else {
      cyclesToGo = 1;
    }

    if (cyclesToGo > 0) {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("SRI:L C=%d, S=%d, D=%d", cyclesToGo, _cycleSpeed, _direction);
#endif
      // Step is a blocking call. No problem at low speeds, at higher speeds the system swings up, until a loop use serveral seconds.
      _stepper->step(cyclesToGo, _direction, _stepStyle);

      // step is a blocking call, if the time before has been assigned, the duration is short goes longer and longer
      _lastLoopTime = millis();
    }
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void forward(int aSpeed) {
    _cycleSpeed = aSpeed / 60.0 * _resolution;

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SRI:Fw S=%d, C=%d", aSpeed, _cycleSpeed);
#endif
    _direction = FORWARD;
    _stepper->setSpeed(aSpeed);
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void backward(int aSpeed) {
    _cycleSpeed = aSpeed / 60.0 * _resolution;

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SRI:Fw S=%d, C=%d", aSpeed, _cycleSpeed);
#endif
    _direction = BACKWARD;
    _stepper->setSpeed(aSpeed);
  }

  //*************************************
  void stop() {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SRI:Sp");
#endif
    _direction = 0;
    _cycleSpeed = 0;
  }
};

#endif