//*****************************************************************
//* Class Buzzer - Header
//*
//*  Beeps in "NumberOfCycles * [OnDuration + OffDuration] + BreakDuration" with Frequency
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

#ifndef EASY_BUZZER_H
#define EASY_BUZZER_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Actuator.h"

class Buzzer : public Actuator
{
private:
  int _pin;
  int _frequency; // {Hz]
  int _onDuration; // [ms]
  int _offDuration; // [ms]
  int _numberOfCycles; // [ms]
  int _breakDuration; // [ms}
  bool _fixFrequency;
  int _maxFrequency; // {Hz] used when _fixFrequency=false
  int _lastFrequency;
  int _currentFrequency;

  //*************************************
  void Init(int aPin, int aFrequency, int aOnDuration, int aOffDuration, int aNumberOfCycles, int aBreakDuration);

public:
  // Beeps depending of input on same frequency, alternating in onDuration and offDuration but only a aNumberOfCycles times. Input correspond to on/off
  Buzzer(int aPin, int aFrequency, int aOnDuration, int aOffDuration, int aNumberOfCycles, int aBreakDuration);

  // Beeps depending of input on same frequency, alternating in onDuration and offDuration. Input correspond to on/off
  Buzzer(int aPin, int aFrequency, int aOnDuration, int aOffDuration);

  // Beeps depending of input on same frequency. Input correspond to on/off.
  Buzzer(int aPin, int aFrequency);

  // Maps input range to the frequency range from aMinFrequency...aMaxFrequency
  Buzzer(int aPin, int aMinFrequency, int aMaxFrequency);

  void Setup();
  void Loop();
  void Act(Input* aInput);
};
#endif
