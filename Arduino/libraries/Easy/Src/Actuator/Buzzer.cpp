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

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Kernel\Actuator.h"
#include "Buzzer.h"

// Libraries
#include <EasyBuzzer.h> // https://github.com/evert-arias/EasyBuzzer

void Buzzer::Init(int aPin, int aFrequency, int aOnDuration, int aOffDuration, int aNumberOfCycles, int aBreakDuration)
{
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("BZ(%d):C Pin=%d, Fq=%d, On=%d, Off=%d, n=%d, B=%d", _id, aPin, aFrequency, aOnDuration, aOffDuration, aNumberOfCycles, aBreakDuration);
#endif
  _pin = aPin;
  _frequency = aFrequency;
  _onDuration = aOnDuration;
  _offDuration = aOffDuration;
  _numberOfCycles = aNumberOfCycles;
  _breakDuration = aBreakDuration;
  _fixFrequency = true;
  _lastFrequency = 0;
  _currentFrequency = 0;
}

//*************************************
// Beeps depending of input on same frequency, alternating in onDuration and offDuration but only a aNumberOfCycles times. Input correspond to on/off
Buzzer::Buzzer(int aPin, int aFrequency, int aOnDuration, int aOffDuration, int aNumberOfCycles, int aBreakDuration) : Actuator(CreateElementId(EbtActuator, EkiAnalog, ANALOG_BUZZER_INDEX))
{
  Init(aPin, aFrequency, aOnDuration, aOffDuration, aNumberOfCycles, aBreakDuration);
}

//*************************************
// Beeps depending of input on same frequency, alternating in onDuration and offDuration. Input correspond to on/off
Buzzer::Buzzer(int aPin, int aFrequency, int aOnDuration, int aOffDuration) : Actuator(CreateElementId(EbtActuator, EkiAnalog, ANALOG_BUZZER_INDEX))
{
  Init(aPin, aFrequency, aOnDuration, 0, 1, 0);
}

//*************************************
// Beeps depending of input on same frequency. Input correspond to on/off.
Buzzer::Buzzer(int aPin, int aFrequency) : Actuator(CreateElementId(EbtActuator, EkiAnalog, ANALOG_BUZZER_INDEX))
{
  Init(aPin, aFrequency, 0, 0, 1, 0);
}

//*************************************
// Maps input range to the frequency range from aMinFrequency...aMaxFrequency
Buzzer::Buzzer(int aPin, int aMinFrequency, int aMaxFrequency) : Actuator(CreateElementId(EbtActuator, EkiAnalog, ANALOG_BUZZER_INDEX))
{
  Init(aPin, aMinFrequency, 0, 0, 1, 0);
  _fixFrequency = false;
  _frequency = aMinFrequency;
  _maxFrequency = aMaxFrequency;
}

//*************************************
void Buzzer::Setup()
{
  EasyBuzzer.setPin(_pin);
}

//*************************************
void Buzzer::Loop()
{
  EasyBuzzer.update();
}

//*************************************
void Buzzer::Act(Input* aInput)
{
  _lastFrequency = _currentFrequency;
  if (aInput->Value() == 0)
  {
    EasyBuzzer.stopBeep();
    _currentFrequency = 0;
  }
  else
  {
    _currentFrequency = _fixFrequency ? _frequency : aInput->Map(_frequency, _maxFrequency);
    if (_currentFrequency != _lastFrequency) {
      EasyBuzzer.stopBeep();
#ifdef LOG_LOOP
      if (!_fixFrequency)
      {
        GetLog()->printf("BZ(%d):A Fq=%d", _id, _currentFrequency);
      }
#endif
      if (_onDuration > 0 && _offDuration > 9)
      {
        EasyBuzzer.beep(
          _currentFrequency,
          _onDuration,
          _offDuration,
          _numberOfCycles,   // Number of tones per cycle
          _breakDuration,  // Break time [ms]
          9999  // Cycles (many results in endless, is switched off again by logic)
        );
      }
      else
      {
        EasyBuzzer.beep(
          _currentFrequency,  // Frequency in Hertz.
          1   // The number of beeps.
        );
      }
    }
  }
}
