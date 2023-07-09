//*****************************************************************
//* Class AdafruitI2cShield - Header
//*
//* Internal Class, implements a singleton to the Adafruit I2C shields
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

// Library
#include "AdafruitI2cShield.h"

// Initialize static members (create at first use)
LinkedList<AdafruitShield*>* AdafruitI2cShield::_shields = NULL;

//*************************************
Adafruit_MotorShield* AdafruitI2cShield::getMotorShield(unsigned int aBusAddress) {
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("A2:CM A=%u", aBusAddress);
#endif

  if (_shields == NULL) {
    // Create at first use
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("A2:CM L");
#endif    
    _shields = new LinkedList<AdafruitShield*>();
  }

  // Search existing
  for (int i = 0; i < _shields->size(); i++) {
    AdafruitShield* shieldRec = _shields->get(i);
    if (shieldRec->BusAddress == aBusAddress) {
#ifdef LOG_SETUP_DEBUG
  GetLog()->println("A2:CM F");
#endif      
      return shieldRec->MotorShield;
    }
  }

  // Nothing found, create new one
#ifdef LOG_SETUP
  GetLog()->printf("A2:CM C %d", aBusAddress);
#endif

  Adafruit_MotorShield* motorShield = new Adafruit_MotorShield(aBusAddress);
  _shields->add(new AdafruitShield(aBusAddress, motorShield));

  return motorShield;
}

//*************************************
Adafruit_PWMServoDriver* AdafruitI2cShield::getPwmServoShield(unsigned int aBusAddress) {

#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("A2:CS A=%u", aBusAddress);
#endif

  if (_shields == NULL) {
    // Create at first use
#ifdef LOG_SETUP_DEBUG
  GetLog()->println("A2:CS F");
#endif      
	
    _shields = new LinkedList<AdafruitShield*>();
  }

  // Search existing
  for (int i = 0; i < _shields->size(); i++) {
    AdafruitShield* shieldRec = _shields->get(i);
    if (shieldRec->BusAddress == aBusAddress) {
#ifdef LOG_SETUP_DEBUG
      GetLog()->println("A2:CS F");
#endif
      return shieldRec->ServoShield;
    }
  }

  // Nothing found, create new one
#ifdef LOG_SETUP
  GetLog()->println("A2:CS C %d", aBusAddress);
#endif
  Adafruit_PWMServoDriver* servoShield = new Adafruit_PWMServoDriver(aBusAddress);
  servoShield->begin();
  _shields->add(new AdafruitShield(aBusAddress, servoShield));
  return servoShield;
}