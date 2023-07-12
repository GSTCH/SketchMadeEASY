//*****************************************************************
//* Example18 - Stepper angle controlled by joystick
//*
//* Hardware:
//* - Stepper motor
//* - Stepper motor shield (L298n oder L9110h)
//* - Analog joystick with 10kOhm Potentiometer
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard.
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Arduino quick and easy
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
// Parameter Motor Shield like L9110
#define STEPPER_PIN1 9
#define STEPPER_PIN2 10
#define STEPPER_PIN3 11
#define STEPPER_PIN4 12
// Parameter Adafruit MotorShield V2 
#define STEPPER_NR 2
#define STEPPER_RPM 20
#define STEPPER_MIN_ANGLE -180
#define STEPPER_MAX_ANGLE 180

// Stepper motor:  Moons PG22L71.7
#define STEPPER_RESOLUTION 20
#define STEPPER_GEARRATIO 71

// Parameter JoyStick
#define JOYSTICK_AXIS_PIN A10

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Define Actuators:
  ServoStepperPositionI2C* stepper = new ServoStepperPositionI2C(STEPPER_NR, STEPPER_RESOLUTION, STEPPER_GEARRATIO, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RPM);

  //** Define Input
  JoystickAxis* xAxis = new JoystickAxis(JOYSTICK_AXIS_PIN, false);

  //** Define logic with condition and relation
  Relation1to1* relationServo = new Relation1to1(NULL, stepper, xAxis);
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