//*****************************************************************
//* Example 03-DimmingLedWithSwitch
//*
//* Example of a combination of a switch with two positions  
//* and a variable output. The lamp lights depending of switch
//* on/off and the amount of the analog value.
//*
//* Hardware:
//* - Switch with two Position (On/Off) on Pin 14(Pulldown internal, no Resistor needed)
//* - LED with 220 Ohm on Pin 6 / Pin 13 is OnBoard LED --> no additional hardware
//* - Potentiometer 10kOhm at Pin A0
//*
//* Hardware:
//* - LED with 220 Ohm on Pin 6 / Pin 13 is OnBoard LED --> no additional hardware
//* - Potentiometer 10kOhm at Pin A0
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example is also a picture of the breadboard.
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

#include <Easy.h>

//*****************************************************************
#define SWITCH_PIN 39
#define LED_PIN 6
#define ONBOARD_LED_PIN 13
#define POTI_PIN A0

void setup() {
  //((*** Initialize: Configure your sketch here....

  //** Create actuator:
  // A variable output has a range of 0...255. It uses a PWM pin.
  VariableOutput* led = new VariableOutput(LED_PIN);

  //** Create input:
  // Switch as input for condition. A switch with two positions 
  // knows the value On and Off.
  Switch2Position* switchOnOff = new Switch2Position(SWITCH_PIN);

  // Input for the actuator is a variable input has a range 
  // of 0...1023. This is an analog pin. the range is autmatic mapped.
  VariableInput* poti = new VariableInput(POTI_PIN);

  //** Define logic with conditions and relations
  // Define relation when button is on
  CompareCondition* conditionSwitchOn = new CompareCondition(switchOnOff, OpEQ, Switch2Position::On);
  Relation1to1* switchOnRelation = new Relation1to1(conditionSwitchOn, led, poti);

  // Define relation when button is off
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
