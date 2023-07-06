//*****************************************************************
//* Class MotorShieldAdafruitV2 - Header
//*
//* Internal class to set command of a motor with motor shield V2
//* from Adafruit (and compatibles).
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

#ifndef EASY_MOTORSHIELDADAFRUITV2_H
#define EASY_MOTORSHIELDADAFRUITV2_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "MotorShieldBase.h"
#include "AdafruitI2cShield.h"
#include "I2cBus.h"
#include <Arduino.h>

#define I2CBUS_TIMEOUT 1000
#define I2CBUS_FREQUENCY 1600

class MotorShieldAdafruitV2 : public MotorShieldBase {
private:
  int _motorNr;
  Adafruit_DCMotor* _motor;

protected:

public:
  //*************************************
  //* aMotorNr : Number of motor on shield
  //* aBusAdddress : I2C Address of the shield
  MotorShieldAdafruitV2(int aMotorNr, int aBusAdddress = 0x60)
    : MotorShieldBase() {

#ifdef LOG_SETUP
    GetLog()->printf("MA(%d):C", aMotorNr);
#endif

    if (aMotorNr > 4 || aMotorNr < 1) {
#ifdef LOG_SETUP
      GetLog()->printf("MA:C inv MNr %d", aMotorNr);
#endif
      aMotorNr = 1;
    }

    _motorNr = aMotorNr;
    Adafruit_MotorShield* shield = AdafruitI2cShield::getMotorShield(aBusAdddress);

    if (shield == NULL) {
#ifdef LOG_SETUP
      GetLog()->printf("MA(Mo=%d):S No shdObj", _motorNr);
#endif
      return;
    }

    _motor = shield->getMotor(_motorNr);
    if (_motor == NULL) {
#ifdef LOG_SETUP
      GetLog()->printf("MA(Mo=%d):S No motObj", _motorNr);
#endif
    }

    //*** next line freeze ?!?! ***************
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("MA(Mo=%d):S begin", _motorNr);
#endif

    //TwoWire* i2c = CI2cBus::GetBus(I2CBUS_TIMEOUT);
    //if (!shield->begin(I2CBUS_FREQUENCY, i2c)) {
    if (!shield->begin()) {
      // create with the default frequency 1.6KHz with Timeout 1000
#ifdef LOG_SETUP
      GetLog()->printf("MA(Mo=%d):S wire?!", _motorNr);
#endif
    }

    if (_motor != NULL) {
      stop();
    }
  }

  //*************************************
  //* aSpeed [1...255]
  void forward(int aSpeed) {
    _motor->run(FORWARD);
    _motor->setSpeed(aSpeed);
  }

  //*************************************
  //* aSpeed [1...255]
  void backward(int aSpeed) {
    _motor->run(BACKWARD);
    _motor->setSpeed(aSpeed);
  }

  //*************************************
  void stop() {
    _motor->run(RELEASE);
    _motor->setSpeed(0);
  }
};
#endif