//*****************************************************************
//* Example 02-DimmingLed
//*
//* Use case for a variable input and variable output.
//* Shows how to make an actuator depending of the value an input.
//*
//* Hardware:
//* - LED with 220 Ohm on Pin 6 / Pin 13 is OnBoard LED --> no additional hardware
//* - Potentiometer 10kOhm at Pin A0
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
#define POTI_PIN A0
#define LED_PIN 6
#define ONBOARD_LED_PIN 13

void setup()
{
    //((*** Initialize: Configure your sketch here....
#ifdef LOG_SETUP
  GetLog()->printf("Example 2 - Dimming lamp");
#endif
  
  // Create actuator
  VariableOutput* led = new VariableOutput(LED_PIN);

  // Create input (as input for the actuator)
  VariableInput* poti = new VariableInput(POTI_PIN);

  // Define relation (condition NULL means "always true")
  Relation1to1* relation = new Relation1to1(NULL, led, poti);
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop()
{
  //*** Run: No additional code is required

#ifdef LOG_LOOP_DEBUG
  GetLog()->println("Loop");
#endif

  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
