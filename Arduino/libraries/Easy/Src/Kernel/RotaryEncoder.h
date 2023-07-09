//*****************************************************************
//* Class RotaryEncoder - Header
//*
//* Internal base class iplement logic of rotary encoder.
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

#ifndef EASY_ROTARYENCODE_H
#define EASY_ROTARYENCODE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"

class RotaryEncoder {
private:
  int _sensorAPin;
  int _sensorBPin;
  float _ppr;
  int _interruptDataIdx;

  // To calc the changes since the last loop, this member save the data of last loop.
  int _previousPos = 0;
  float _previousTime = 0;
  int _previousRotationalSpeed;

protected:
  static int _encoderCount;

public:
  //****
  //* RPM of the encoder.
  float RotationalSpeed = 0;
  float FilteredRotationalSpeed = 0;
  float DurationSinceLastLoop = 0;

  //*************************************
  RotaryEncoder(int aSensorAPin, int aSensorBPin, float aPPR);

  //*************************************
  void Setup();

  //*************************************
  void Loop();
};

#endif