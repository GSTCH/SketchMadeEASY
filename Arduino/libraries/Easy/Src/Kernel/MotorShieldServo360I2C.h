//*****************************************************************
//* Class Servo360I2C - Header
//*
//* Internal class to set command of a servo 360 using a I2C PWM/Servo shield
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

#ifndef EASY_MOTORSHIELDSERVO360I2C_H
#define EASY_MOTORSHIELDSERVO360I2C_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include <Arduino.h>

#ifndef I2C_SERVO_FREQ
// Servos run at ~50 Hz updates
#define I2C_SERVO_FREQ 50               
#endif

#ifndef SERVO_MAXBACKWARD_TIME_I2C
// This is the rounded 'minimum' microsecond length
#define SERVO_MAXBACKWARD_TIME_I2C 1000  
#endif

#ifndef SERVO_MAXFORWARD_TIME_I2C
// This is the rounded 'maximum' microsecond length 
#define SERVO_MAXFORWARD_TIME_I2C 2000  
#endif

#ifndef SERVO_STOP_TIME_I2C
// (SERVO_MAXBACKWARD_TIME_I2C + SERVO_MAXFORWARD_TIME_I2C) / 2
#define SERVO_STOP_TIME_I2C 1500        
#endif

class MotorShieldServo360I2C : public MotorShieldBase {
private:
  int _servoNr;
  int _maxForwardMillis;
  int _stopMillis;
  int _maxBackwardMillis;
  Adafruit_PWMServoDriver* _servoShield;

public:
  //*************************************
  MotorShieldServo360I2C(int aServoNr, int aBusAddress = 0x40)
    : MotorShieldBase() {
    _servoNr = aServoNr;
    _maxForwardMillis = SERVO_MAXFORWARD_TIME_I2C;
    _stopMillis = SERVO_STOP_TIME_I2C;
    _maxBackwardMillis = SERVO_MAXBACKWARD_TIME_I2C;
    _servoShield = AdafruitI2cShield::getPwmServoShield(aBusAddress);
  }

//*************************************
  MotorShieldServo360I2C(int aServoNr, int aMaxForwardMillis, int aStopMillis, int aMaxBackwardMillis, int aBusAddress = 0x40)
    : MotorShieldBase() {
    _servoNr = aServoNr;
    _maxForwardMillis = aMaxForwardMillis;
    _stopMillis = aStopMillis;
    _maxBackwardMillis = aMaxBackwardMillis;
    _servoShield = AdafruitI2cShield::getPwmServoShield(aBusAddress);
  }  

  //*************************************
  void Setup() {
    _servoShield->begin();
    _servoShield->setOscillatorFrequency(27000000);
    _servoShield->setPWMFreq(I2C_SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    stop();
  }

  //*************************************
  void forward(int aSpeed) {
long val = _stopMillis + map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, 0, _stopMillis-_maxForwardMillis);
#ifdef _LOG_LOOP_DEBUG
    GetLog()->printf("S3I2C:F Spd=%d, Val=%d", aSpeed, val);
#endif
    _servoShield->writeMicroseconds(_servoNr, val);
  }

  //*************************************
  void backward(int aSpeed) {
long val = _stopMillis - map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, 0, _maxBackwardMillis-_stopMillis);
#ifdef _LOG_LOOP_DEBUG
    GetLog()->printf("S3I2C:B Spd=%d, Val=%d", aSpeed, val);
#endif	 
    _servoShield->writeMicroseconds(_servoNr, val);
  }

  //*************************************
  void stop() {
    _servoShield->writeMicroseconds(_servoNr, _stopMillis);
  }
};

#endif