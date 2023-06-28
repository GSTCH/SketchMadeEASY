//*****************************************************************
//* Class AdafruitI2cShield - Header
//*
//* Internal Class, implements a singleton to the Adafruit I2C shields
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

#ifndef EASY_ADAFRUITI2CSHIELD_H
#define EASY_ADAFRUITI2CSHIELD_H

// Library
#include <LinkedList.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "AdafruitShield.h"

//*************************************
//* class definition
//*************************************
class AdafruitI2cShield {
private:
  // Mode address of at I2C is unique and can be used as key. 
  // To solve some bytes memory ony one list is used.
  static LinkedList<AdafruitShield*>* _shields;

public:
  //*************************************
  //* Search for existing board with the address in parameter. When not found,
  //* it creates one. When another shield exists at the address, the function
  //* returns NULL.
  static Adafruit_MotorShield* getMotorShield(unsigned int aBusAddress = 0x60);
  
  //*************************************
  //* Search for existing board with the address in parameter. When not found,
  //* it creates one. When another shield exists at the address, the function
  //* returns NULL.
  static Adafruit_PWMServoDriver* getPwmServoShield(unsigned int aBusAddress = 0x40);
};
#endif
