//*****************************************************************
//* Test for Buzzer
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*
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

#define LOG
#define LOG_LOOP
#include <Easy.h>

//*****************************************************************
// Parameter Iterator
#define ITERATOR_VALUE_START 0 // [%]
#define ITERATOR_VALUE_END 100 // [%]
#define ITERATOR_STEPWIDTH 10
#define ITERATOR_STEPDURATION_MSEC 500

// Parameter Buzzer
#define BUZZER_PIN 4
#define BUZZER_MIN_FREQUENCY 50
#define BUZZER_MAX_FREQUENCY 1000


void setup() {

//((*** Initialize: Configure your sketch here...
#ifdef LOG_SETUP
  GetLog()->printf("Buzzer Test");
#endif

  Buzzer* buzzer = new Buzzer(BUZZER_PIN, BUZZER_MIN_FREQUENCY, BUZZER_MAX_FREQUENCY);
  IteratorValue* iteratorValue = new IteratorValue(ITERATOR_VALUE_START, ITERATOR_VALUE_END,  ITERATOR_STEPWIDTH, ITERATOR_STEPDURATION_MSEC, cmMin2Max2Min);
  Relation1to1* relation = new Relation1to1(NULL, buzzer, iteratorValue);
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required

#ifdef LOG_LOOP_DEBUG
  GetLog()->println("Loop");
#endif

  ControlManagerFactory::GetControlManager()->Loop();

  delay(5);
}
