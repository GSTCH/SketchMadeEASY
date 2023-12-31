//*****************************************************************
//* Example 02-DimmingLed
//*
//* Use case for a variable input and variable output.
//* Shows how to make an actuator depending of the value an input.
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
#define POTI_PIN A0
#define LED_PIN 6
#define ONBOARD_LED_PIN 13

void setup()
{
    //((*** Initialize: Configure your sketch here....
 
  //** Create actuator:
  // A variable output has a range from 0 to 255. It's needs PWM pin.
  VariableOutput* led = new VariableOutput(LED_PIN);

  //** Create input 
  // In this case we define the input for the actuator into the action.
  // This is an analog pin with a value range of 0...1023.
  VariableInput* poti = new VariableInput(POTI_PIN);

  //** Define logic with conditions and relations
  // Condition NULL means "always true"
  Relation1to1* relation = new Relation1to1(NULL, led, poti);
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop()
{
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
