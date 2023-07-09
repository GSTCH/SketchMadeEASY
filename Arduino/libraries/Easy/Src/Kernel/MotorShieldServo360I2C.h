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

#define SERVO_FREQ 50               // Analog servos run at ~50 Hz updates
#define SERVO_MAXBACKWARD_TIME 1000  // This is the rounded 'minimum' microsecond length
#define SERVO_MAXFORWARD_TIME 2000  // This is the rounded 'maximum' microsecond length 
#define SERVO_STOP_TIME 1500        // (SERVO_MAXBACKWARD_TIME + SERVO_MAXFORWARD_TIME) / 2


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
    _maxForwardMillis = SERVO_MAXFORWARD_TIME;
    _stopMillis = SERVO_STOP_TIME;
    _maxBackwardMillis = SERVO_MAXBACKWARD_TIME;
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
    _servoShield->setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    stop();
  }

  //*************************************
  void forward(int aSpeed) {
    _servoShield->writeMicroseconds(_servoNr, map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, _stopMillis, _maxForwardMillis));
  }

  //*************************************
  void backward(int aSpeed) {
    _servoShield->writeMicroseconds(_servoNr, map(aSpeed, _minMotorShieldSpeed, _maxMotorShieldSpeed, _stopMillis, _maxBackwardMillis));
  }

  //*************************************
  void stop() {
    _servoShield->writeMicroseconds(_servoNr, _stopMillis);
  }
};

#endif