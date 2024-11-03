//*****************************************************************
//* Class CI2cBus - Header
//*
//* Internal Class, implements a singleton to the I2C bus
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

#ifdef ARDUINO_ARCH_RENESAS
#ifndef WIRE1_SCL_PIN
#define WIRE1_SCL_PIN 0
#endif

#ifndef WIRE1_SDA_PIN
#define WIRE1_SDA_PIN 1
#endif

    _i2cBus = new TwoWire(WIRE1_SCL_PIN, WIRE1_SDA_PIN);
#elif ARDUINO_ARCH_ESP32
    _i2cBus = new TwoWire(0);
#else
    _i2cBus = new TwoWire();
#endif  
    if (aTimeout > 0) {
      setTimeout(aTimeout);
    }
  }
  return _i2cBus;
}

//*************************************
void I2cBus::setTimeout(unsigned int aTimeout) {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("IC:T %d", aTimeout);
#endif
#ifndef ARDUINO_ARCH_RENESAS
  if (_i2cBus == NULL) {
    _i2cBus->setTimeout(aTimeout);
  }
#endif
}
