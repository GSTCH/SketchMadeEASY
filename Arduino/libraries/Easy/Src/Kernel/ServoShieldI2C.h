//*****************************************************************
//* Class ServoShieldI2C - Header
//*
//* Internal class to set command of a servo using a I2C PWM/Servo shield
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

#ifndef EASY_SERVOSHIELDI2C_H
#define EASY_SERVOSHIELDI2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "ServoShieldBase.h"
#include <Adafruit_PWMServoDriver.h>

#ifndef EASY_SERVO_FREQ
#define EASY_SERVO_FREQ 50                    // Analog servos run at ~50 Hz updates
#endif

#ifndef EASY_SERVO_MIN_PULSEWIDTH_MSEC
#define EASY_SERVO_MIN_PULSEWIDTH_MSEC 600   // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#endif

#ifndef EASY_SERVO_MAX_PULSEWIDTH_MSEC
#define EASY_SERVO_MAX_PULSEWIDTH_MSEC 2400  // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#endif

#ifndef EASY_OSCILLATORFREQUENCY
#define EASY_OSCILLATORFREQUENCY 27000000
#endif

class ServoShieldI2C : public ServoShieldBase {
private:
  int _servoNr;
  int _minAngle;
  int _maxAngle;
  int _minPulseWidthMillis;
  int _maxPulseWidthMillis;

  Adafruit_PWMServoDriver* _servoShield;

public:
  //*************************************
  ServoShieldI2C(int aServoNr, int aMinAngle, int aMaxAngle, int aBusAddress = 0x40)
    : ServoShieldBase() {
    _servoNr = aServoNr;
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
    _minPulseWidthMillis = EASY_SERVO_MIN_PULSEWIDTH_MSEC;
    _maxPulseWidthMillis = EASY_SERVO_MAX_PULSEWIDTH_MSEC;
    _servoShield = AdafruitI2cShield::getPwmServoShield(aBusAddress);
  }
  
  //*************************************
  ServoShieldI2C(int aServoNr, int aMinAngle, int aMaxAngle, int aMinAngleMillis, int aMinPulseWidthMillis, int aMaxPulseWidthMillis, int aBusAddress = 0x40)
    : ServoShieldBase() {
    _servoNr = aServoNr;
    _minAngle = aMinAngle;
    _maxAngle = aMaxAngle;
    _minPulseWidthMillis = aMinPulseWidthMillis;
    _maxPulseWidthMillis = aMaxPulseWidthMillis;
    _servoShield = AdafruitI2cShield::getPwmServoShield(aBusAddress);
  }

  //*************************************
  void Setup() {
    _servoShield->begin();
    _servoShield->setOscillatorFrequency(EASY_OSCILLATORFREQUENCY);
    _servoShield->setPWMFreq(EASY_SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    angle((_minAngle+_maxAngle)/2);
  }

  //*************************************
  void angle(int aAngle) {
    _servoShield->writeMicroseconds(_servoNr, map(aAngle, _minAngle, _maxAngle, _minPulseWidthMillis, _maxPulseWidthMillis));
  }
};

#endif