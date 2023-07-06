//*****************************************************************
//* Class CI2cBus - Header
//*
//* Internal Class, implements a singleton to the I2C bus
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

// Library
#include "I2cBus.h"
#include "..\Common\Log.h"

// Initialize static members (create at first use)
TwoWire* I2cBus::_i2cBus = NULL;

//*************************************
TwoWire* I2cBus::getBus(unsigned int aTimeout) {
  if (_i2cBus == NULL) {
#ifdef LOG_SETUP
    GetLog()->printf("IC:G %d", aTimeout);
#endif
    _i2cBus = new TwoWire();
    if (aTimeout > 0) {
      _i2cBus->setWireTimeout(aTimeout);
    }
  }

  return _i2cBus;
}

//*************************************
void I2cBus::setTimeout(unsigned int aTimeout) {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("IC:T %d", aTimeout);
#endif
  if (_i2cBus == NULL) {
    _i2cBus->setWireTimeout(aTimeout);
  }
}
