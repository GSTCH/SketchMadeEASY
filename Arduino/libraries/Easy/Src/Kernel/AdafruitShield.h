//*****************************************************************
//* Struct AdafruitShield - Header
//*
//* Internal class to save data of a I2C shield
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

#ifndef EASY_ADAFRUITSHIELD_H
#define EASY_ADAFRUITSHIELD_H

// Internal types
class AdafruitShield {
public:
  int BusAddress;
  Adafruit_MotorShield* MotorShield;
  Adafruit_PWMServoDriver* ServoShield;

  AdafruitShield(int aBusAddress, Adafruit_MotorShield* aMotorShield) {
    BusAddress = aBusAddress;
    MotorShield = aMotorShield;
    ServoShield = NULL;
  }

  AdafruitShield(int aBusAddress, Adafruit_PWMServoDriver* aServoShield) {
    BusAddress = aBusAddress;
    MotorShield = NULL;
    ServoShield = aServoShield;
  }
};

#endif