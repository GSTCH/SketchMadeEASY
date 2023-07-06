//*****************************************************************
//* Example 01-SwitchAndLamp
//*
//* Example of a combination of a DigitalInput and DigitalOutput.
//* Shows a simple relation of an input to an actuator.
//*
//*  Hardware:
//* - Switch with two Position (On/Off) on Pin 14(Pulldown internal, no Resistor needed)
//* - LED with 220 Ohm on Pin 6 / Pin 13 is OnBoard LED --> no additional hardware
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
#define SWITCH_PIN 14
#define LED_PIN 6
#define ONBOARD_LED_PIN 13

void setup() {
  //((*** Initialize: Configure your sketch here....
  //** Create input:
  // A switch with two positions knows the value On and Off.
  Switch2Position* switchOnOff = new Switch2Position(SWITCH_PIN);

  //** Create actuator:
  // A DigitalOutput knows the value On and Off.
  DigitalOutput* led = new DigitalOutput(LED_PIN);

  //** Define logic with conditions and relations
  // Define relation when switch is on
  CompareCondition* conditionSwitchOn = new CompareCondition(switchOnOff, OpEQ, Switch2Position::On);
  Relation1to1* switchOnRelation = new Relation1to1(conditionSwitchOn, led, FixValue::On());

  // Define relation when switch is off
  CompareCondition* conditionSwitchOff = new CompareCondition(switchOnOff, OpEQ, Switch2Position::Off);
  Relation1to1* switchOffRelation = new Relation1to1(conditionSwitchOff, led, FixValue::Off());
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
