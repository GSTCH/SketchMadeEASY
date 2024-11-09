//*****************************************************************
//* Example 81-RelationChangeEvent
//*
//* Test relation changed event to implement a blinking LED.
//* Instead define an actuator, classic Arduino API with SetOutput 
//* has been used.
//* 
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2024 by Hans Rothenbühler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************

#include <Easy.h>

//*****************************************************************
#define TIMER_INTERVAL_MSEC 1500
#define LED_PIN 6

void setup() {
  //((*** Initialize: Configure your sketch here....

  //** Create input:
  // Input changes value periodically and toggles between High and Low.
  Timer* timer = new Timer(TIMER_INTERVAL_MSEC, true);

  //** Create actuator. 
  // A DigitalOutput knows the value On and Off.
  pinMode(LED_BUILTIN, OUTPUT);

  //** Define logic with conditions and relations
  // Define relation when timer value changes to High
  CompareCondition* conditionLedOn = new CompareCondition(timer, OpEQ, Timer::High);
  Relation1to1* relationLedOn = new Relation1to1(conditionLedOn, NULL, 0);
  relationLedOn->RegisterStateChangedEvent(ChangeRelationHighStateEventHandler);

  // Define relation when timer value changes to High
  CompareCondition* conditionLedOff = new CompareCondition(timer, OpEQ, Timer::Low);
  Relation1to1* relationLedOff = new Relation1to1(conditionLedOff, NULL, 0);
  relationLedOff->RegisterStateChangedEvent(ChangeRelationLowStateEventHandler);

  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}

//*****************************************************************
void ChangeRelationHighStateEventHandler(bool aState)
{
  if (aState)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void ChangeRelationLowStateEventHandler(bool aState)
{
  if (aState)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
