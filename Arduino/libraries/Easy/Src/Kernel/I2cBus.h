//*****************************************************************
//* Class CI2cBus - Header
//*
//* Internal Class, implements a singleton to the I2C bus. 
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

#ifndef EASY_I2CBUS_H
#define EASY_I2CBUS_H

// Library
#include <Wire.h>
#include "..\Common\BuildDefinition.h" // has to be the first 

//*************************************
//* class definition
//*************************************
class I2cBus {
private:
  // Mode I2C is unique 
  static TwoWire* _i2cBus;

public:
  //*************************************
  //* Sometimes the I2C bus hangs during setup (mostly using multiple 
  //* shields of I2C bus). In this case a timeout of e.g. 1000 will help.
  static TwoWire* getBus(unsigned int aTimeout = 0);
  
  //*************************************
  //* Change timeout of I2C bus
  static void setTimeout(unsigned int aTimeout);
};
#endif
