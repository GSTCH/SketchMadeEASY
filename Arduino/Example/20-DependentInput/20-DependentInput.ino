//*****************************************************************
//* Example 20-DependentInput
//*
//* Input that defines the brightness of the LED depends on the 
//* position of a switch. 
//*
//*  Hardware:
//* - Switch with three Position 
//* - LED with 220 Ohm on Pin 6 / Pin 13 is OnBoard LED --> no additional hardware

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
#define PIN_SWITCH_MODE1 40
#define PIN_SWITCH_MODE2 42
#define INPUT_VALUES_COUNT 3
#define LED_PIN 6
#define ONBOARD_LED_PIN 13

void setup()
{
  //((*** Initialize: Configure your sketch here....
  // Switch define the to use input
  Switch3Position* modeSelectorSwitch = new Switch3Position(PIN_SWITCH_MODE1, PIN_SWITCH_MODE2);

  // DependentInput use the input in relation of the switch value.
  DependentInput* dependentInput = new DependentInput(
    modeSelectorSwitch, 
    FixValue::Off(), // Pos0: Off
    FixValue::Percent(50), // Pos1: 50%
    new VariableInput(A0)); // Pos2: Variable: 0..100%

  // Create actuator
  VariableOutput* led = new VariableOutput(LED_PIN);

  // Define logic with a relation (without any condition)
  Relation1to1* switchOnRelation = new Relation1to1(NULL, led, dependentInput);
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
