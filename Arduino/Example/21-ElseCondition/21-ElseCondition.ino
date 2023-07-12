//*****************************************************************
//* Example 21-ElseCondition
//*
//* A DigitalOutout/LED knows the value on and off. The other
//* DigitalOutout/LED does the same but inverted. 
//*
//* Hardware:
//* - LED with 220 Ohm on Pin 6
//* - LED with 220 Ohm on Pin 38
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard.
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#include <Easy.h>

//*****************************************************************
// Parameter switch
#define LED1_PIN 6
#define LED2_PIN 38
#define TIMER_INTERVAL_MSEC 1500

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Create actuators
  DigitalOutput* led1 = new DigitalOutput(LED1_PIN);
  DigitalOutput* led2 = new DigitalOutput(LED2_PIN);

  //** Create input.
  Timer* timer = new Timer(TIMER_INTERVAL_MSEC, true);

  //** Define logic with condition and relation
  // Condition when Timer is high 
  CompareCondition* conditionLed1On = new CompareCondition(timer, OpEQ, Timer::High);  
  Relation1to1* relationLed1On = new Relation1to1(conditionLed1On, led1, FixValue::On());

  // Same for second actuator but inverted
  ElseCondition* conditionLed2On = new ElseCondition(conditionLed1On);
  Relation1to1* relationLed2On = new Relation1to1(conditionLed2On, led2, FixValue::On());

  // Condition when Timer is low
  CompareCondition* conditionLed1Off = new CompareCondition(timer, OpEQ, Timer::Low);
  Relation1to1* relationLed1Off = new Relation1to1(conditionLed1Off, led1, FixValue::Off());

  // Same for second actuator but inverteds
  ElseCondition* conditionLed2Off = new ElseCondition(conditionLed1Off);
  Relation1to1* relationLed2Off = new Relation1to1(conditionLed2Off, led2, FixValue::Off());
// ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  delay(5);
}
