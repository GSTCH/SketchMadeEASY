//*****************************************************************
//* Class ServoShieldStepperPositionI2C - Header
//*
//* Internal class to set command of a stepper with controlled by
//* Adafruit Motor Shield V2, with controled position.
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

#ifndef EASY_SERVOSHIELDSTEPPERPOSITIONI2C_H
#define EASY_SERVOSHIELDSTEPPERPOSITIONI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "ServoShieldBase.h"
#include "AdafruitI2cShield.h"

#ifndef EASY_STEPPERROTATE_I2C_MAX_CYCLES_PER_SEC
#define EASY_STEPPERROTATE_I2C_MAX_CYCLES_PER_SEC 17  // 1000 PPS/min
#endif

class ServoShieldStepperPositionI2C : public ServoShieldBase {
private:
  Adafruit_StepperMotor* _stepper;
  Adafruit_MotorShield* _shield;
  float _degreePerStep;
  int _cycleSpeed;
  int _currentAngle = 0;
  int _stepsToGo = 0;
  int _resolution;
  int _maxCylcesPerSecond = EASY_STEPPERROTATE_I2C_MAX_CYCLES_PER_SEC;
  EStepStyle _stepStyle;
  unsigned long _lastLoopTime = 0;

public:
  //*************************************
  //* aStepperNr : Number of stepper on shield
  //* aMotorResolution : steps per revolution of the stepper motor (without gear) [PPS]
  //* aRotationSpeed : Speed of the motor [rotations per minute]. 
  //* aStepStyle : Type of stepper motor signal (ssSingle, ssDouble, ssInterleave, ssMicrostep)
  //* aBusAdddress : I2C Address of the shield
  ServoShieldStepperPositionI2C(int aStepperNr, int aMotorResolution, int aRotationSpeed = 60, EStepStyle aStepStyle = ssSingle, int aBusAdddress = 0x60)
    : ServoShieldBase() {
#ifdef LOG_SETUP
    GetLog()->printf("SPI:C N=%d, R=%d, S=%d, A=%d", aStepperNr, aMotorResolution, aRotationSpeed, aBusAdddress);
#endif

    if (aStepperNr > 2 || aStepperNr < 1) {
#ifdef LOG_SETUP
      GetLog()->printf("SPI:C SNr %d to 1", aStepperNr);
#endif
      aStepperNr = 1;
    }

    _resolution = aMotorResolution;
    _degreePerStep = 360.0 / (_resolution * 100);

    // Calculate the speed to turn, limit the parameter by max possible cycles. [cycles/sec]
    _stepStyle = aStepStyle;
    //_cycleSpeed = min(_maxCylcesPerSecond, aRotationSpeed * _resolution / 60.0);
    _cycleSpeed = aRotationSpeed * _resolution / 60.0;


    _shield = AdafruitI2cShield::getMotorShield(aBusAdddress);

    if (_shield == NULL) {
#ifdef LOG_SETUP
      GetLog()->printf("SPI:C No shdObj");
#endif
      return;
    }

    _stepper = _shield->getStepper(_resolution, aStepperNr);
    if (_stepper == NULL) {
#ifdef LOG_SETUP
      GetLog()->printf("SPI:C No stp obj");
#endif
    }
  }

  //*************************************
  void Setup() {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("SPI:S V=%d", _cycleSpeed);
#endif
    if (!_shield->begin()) {
      // create with the default frequency 1.6KHz
#ifdef LOG_SETUP
      GetLog()->printf("SPI:S Motor shield wiring!?");
#endif
    }

    _stepper->setSpeed(_cycleSpeed * 60);  // steps/sec
  }

  //*************************************
  void Loop() {
    if (_stepsToGo != 0) {
      unsigned long currentTime = millis();

      int cyclesInPeriod = 1;
      if (_lastLoopTime > 0) {
        cyclesInPeriod = abs((currentTime - _lastLoopTime) / 1000.0 * _cycleSpeed);

        int maxStepsPerLoop = _maxCylcesPerSecond >> 4;
        if (cyclesInPeriod > maxStepsPerLoop) {
          cyclesInPeriod = maxStepsPerLoop;
        }
        if (cyclesInPeriod > abs(_stepsToGo)) {
          cyclesInPeriod = _stepsToGo;
        }

#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("SPI:L S=%d, C=%d", _stepsToGo, cyclesInPeriod);
#endif
      }

      if (cyclesInPeriod != 0) {
#ifdef LOG_LOOP_DEBUG
        GetLog()->printf("SPI:L C=%d", cyclesInPeriod);
#endif
        // Step block the execution of the sketch to prefent this only short steps are made.
        if (_stepsToGo > 0) {
          _stepper->step(cyclesInPeriod, FORWARD, _stepStyle);
          _stepsToGo -= cyclesInPeriod;
        } else if (_stepsToGo < 0) {
          _stepper->step(cyclesInPeriod, BACKWARD, _stepStyle);
          _stepsToGo += cyclesInPeriod;
        }

        // step is a blocking call, if the time before has been assigned, 
		// the duration is short goes longer and longer
        _lastLoopTime = millis();
      }
    }
  }

  //*************************************
  //* aSpeed: Value in rotations per minute [RPM]
  void angle(int aAngle) {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SPI:A C=%d, A=%d", _currentAngle, aAngle);
#endif
    step(round((_currentAngle - aAngle) / _degreePerStep));
    _currentAngle = aAngle;
  }

  //*************************************
  //* aRotationSpeed : [rotations per minute]
  void speed(int aRotationSpeed) {
    _cycleSpeed = min(_maxCylcesPerSecond, (int)(aRotationSpeed * _resolution / 60.0));

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SPI:Sp V=%d, S=%d", aRotationSpeed, _cycleSpeed);
#endif

    _stepper->setSpeed(_cycleSpeed);  // steps/sec
  }

  //*************************************
  void step(int aSteps) {
    // When calling step() the library block the sketch. To prevent this, calc the 
	// the steps and iterate them through each loop in relation to the speed.
    _stepsToGo += aSteps;
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("SPI:S G=%d, D=%d", _stepsToGo, aSteps);
#endif
  }

  //*************************************
  void resetPosition() {
    _currentAngle = 0;
  }
};

#endif