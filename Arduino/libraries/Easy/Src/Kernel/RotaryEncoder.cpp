//*****************************************************************
//* Class RotaryEncoder - Header
//*
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

#include "RotaryEncoder.h"
#include "..\Common\Log.h"
#include <arduino.h>
// Some defines to increase readablity of code
#define MICROSECOND_IN_ONE_SECOND 1.0e6
#define SECONDS_IN_ONE_MINUTE 60

//*************************************
//* This arrays is shared from CRotaryEncoder objects and the interrupt handler function (IH).
//* The IH calls when A-Signal raising. The IH read the B-Signal to detect rotary direction.
//* "volatile" directive for variables used in an interrupt

#ifndef EASY_MAX_ENCODERS
#define EASY_MAX_ENCODERS 6
#endif


int RotaryEncoder::_encoderCount = 0;

// Pos_i contains step count of rotary encoder, calculated by  interrupt handler function
volatile int Pos_i[EASY_MAX_ENCODERS] = { 0, 0, 0, 0, 0, 0 };

// SensorPin_i defines digital Pin the
volatile int SensorPin_i[EASY_MAX_ENCODERS] = { 0, 0, 0, 0, 0, 0 };

//*************************************
void readEncoder(int aIndex) {
  // Read encoder B when encoder A rises.
  int b = digitalRead(SensorPin_i[aIndex]);

  if (b > 0) {
    // If B is high, increment forward
    Pos_i[aIndex] = Pos_i[aIndex] + 1;
  } else {
    // Otherwise, increment backward
    Pos_i[aIndex] = Pos_i[aIndex] - 1;
  }
}

void readEncoder0() {
  readEncoder(0);
}

void readEncoder1() {
  readEncoder(1);
}

void readEncoder2() {
  readEncoder(2);
}

void readEncoder3() {
  readEncoder(3);
}

void readEncoder4() {
  readEncoder(4);
}

void readEncoder5() {
  readEncoder(5);
}

//*************************************
RotaryEncoder::RotaryEncoder(int aSensorAPin, int aSensorBPin, float aPPR) {
  if (_encoderCount < EASY_MAX_ENCODERS - 1) {
    _interruptDataIdx = _encoderCount++;
  } else {
#ifdef LOG_SETUP
    GetLog()->printf("RE:C max=%d, increase const EASY_MAX_ENCODERS", EASY_MAX_ENCODERS);
#endif
    return;
  }

#ifdef LOG_SETUP
  GetLog()->printf("RE:C(%d) PA=%d, PB=%d, PPR=%d", _interruptDataIdx, aSensorAPin, aSensorBPin, aPPR);
#endif

  _sensorAPin = aSensorAPin;
  _sensorBPin = aSensorBPin;
  _ppr = aPPR;

  _previousTime = micros();
}

//*************************************
void RotaryEncoder::Setup() {
  pinMode(_sensorAPin, INPUT_PULLUP);
  pinMode(_sensorBPin, INPUT_PULLUP);

  Pos_i[_interruptDataIdx] = 0;
  SensorPin_i[_interruptDataIdx] = _sensorBPin;

  switch (_interruptDataIdx) {
    case 0:
      attachInterrupt(digitalPinToInterrupt(_sensorAPin), readEncoder0, RISING);
      break;
    case 1:
      attachInterrupt(digitalPinToInterrupt(_sensorAPin), readEncoder1, RISING);
      break;
    case 2:
      attachInterrupt(digitalPinToInterrupt(_sensorAPin), readEncoder2, RISING);
      break;
    case 3:
      attachInterrupt(digitalPinToInterrupt(_sensorAPin), readEncoder3, RISING);
      break;
    case 4:
      attachInterrupt(digitalPinToInterrupt(_sensorAPin), readEncoder4, RISING);
      break;
    case 5:
      attachInterrupt(digitalPinToInterrupt(_sensorAPin), readEncoder5, RISING);
      break;
  }
}

//*************************************
// Rotary speed has been calculated into the loop. It's also possible into the interrupt handler function.
// Into loop it gives an average over some loops. Additional filter limit to large changes within one loop.
void RotaryEncoder::Loop() {
  // read the position in an atomic block
  // to avoid potential misreads
  int pos = 0;
  noInterrupts();
  pos = Pos_i[_interruptDataIdx];
  interrupts();

  long currentTime = micros();
  DurationSinceLastLoop = 1.0 * (currentTime - _previousTime) / MICROSECOND_IN_ONE_SECOND;  // [sec]

  int delta = pos - _previousPos;
  if (DurationSinceLastLoop > 0) {
    RotationalSpeed = delta / (_ppr * DurationSinceLastLoop) * SECONDS_IN_ONE_MINUTE;  // [RPM, 1/min]
  } else {
    RotationalSpeed = 0;
  }
  // Compute the current speed
  // Low-pass filter
  FilteredRotationalSpeed = 0.85 * FilteredRotationalSpeed + 0.075 * RotationalSpeed + 0.075 * _previousRotationalSpeed;

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("RE:L PS=%d, DT=%d, Du=%d", pos, delta, DurationSinceLastLoop);
#endif

#ifdef PLOT_ROTARYENCODER
  GetLog()->printf("Pos:%d, RPMr:%d, RPMf:%d", pos, (int)RotationalSpeed, (int)FilteredRotationalSpeed);
#endif

  _previousRotationalSpeed = RotationalSpeed;
  _previousTime = currentTime;
  _previousPos = pos;
}
