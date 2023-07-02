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
// Parameter Timer
#define TIMER_INTERVAL_MSEC 1000
// Parameter Buzzer 
#define BUZZER_FREQUENCY 440
#define BUZZER_PIN 4

void setup() {
	
//((*** Initialize: Configure your sketch here....
#ifdef LOG_SETUP
  GetLog()->printf("Buzzer Test");
#endif
  Timer* timer = new Timer(TIMER_INTERVAL_MSEC, true);

   Buzzer* buzzer = new Buzzer(BUZZER_PIN, BUZZER_FREQUENCY);

    //** Define logic with conditions and relations
  // Define relation when timer value changes to High
  CompareCondition* conditionLedOn = new CompareCondition(timer, OpEQ, Timer::High);
  Relation1to1* relationLedOn = new Relation1to1(conditionLedOn, buzzer, FixValue::On());

  // Define relation when timer value changes to Low
  CompareCondition* conditionLedOff = new CompareCondition(timer, OpEQ, Timer::Low);
  Relation1to1* relationLedOff = new Relation1to1(conditionLedOff, buzzer, FixValue::Off());
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
