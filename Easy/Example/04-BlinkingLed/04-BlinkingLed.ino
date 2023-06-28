//*****************************************************************
//* Example 04-BlinkingLed
//*
//* Toggling LED (the most common hello world example with Arduino)
//*
//* Hardware:
//* - LED with 220 Ohm on Pin 6 / Pin 13 is OnBoard LED --> no additional hardware
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
#define TIMER_INTERVAL_MSEC 1500
#define ONBOARD_LED_PIN 13
#define LED_PIN 6

void setup() {
  //((*** Initialize: Configure your sketch here....

  // Input changes value periodically and toggles between High and Low.
  Timer* timer = new Timer(TIMER_INTERVAL_MSEC, true);

  // Create actuator. A DigitalOutput knows the value On and Off.
  DigitalOutput* led = new DigitalOutput(LED_PIN);

  // Define relation when timer value changes to High
  CompareCondition* conditionLedOn = new CompareCondition(timer, OpEQ, Timer::High);
  Relation1to1* relationLedOn = new Relation1to1(conditionLedOn, led, FixValue::On());

  // Define relation when timer value changes to Low
  CompareCondition* conditionLedOff = new CompareCondition(timer, OpEQ, Timer::Low);
  Relation1to1* relationLedOff = new Relation1to1(conditionLedOff, led, FixValue::Off());
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

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
