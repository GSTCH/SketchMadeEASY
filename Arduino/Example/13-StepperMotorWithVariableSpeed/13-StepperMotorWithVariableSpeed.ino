//*****************************************************************
//* Example 13-Stepper motor with variable speed.
//*
//* Stepper motor speed in relation to a potentiometer
//*
//* Hardware:
//* - H-bridge shield to control stepper
//* - stepper motor 
//* - Potentiometer with 10kOhm
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard 
//* with different motor shield types.
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
// H-Bridge shield like L9110, ULN2003, ... 
#define HBRIDGE_PIN1 9
#define HBRIDGE_PIN2 10
#define HBRIDGE_PIN3 11
#define HBRIDGE_PIN4 12
// Adafruit MotorShield V2
#define STEPPER_NR 2
#define MAX_CYCLES_PER_SECOND 1000
// Motor
// Stepper motor:  28BYJ-48
//#define STEPS_PER_ROTATION 32
//#define GEAR_RATIO 64
// Stepper motor: N20
#define GEAR_RATIO 100
#define STEPS_PER_ROTATION 20
#define STEPPER_RESOLUTION STEPS_PER_ROTATION * GEAR_RATIO

// Potentiometer
#define VARIABLE_INPUT_PIN A0

#define SPEED1_RPM 30
#define SPEED2_RPM 3
#define STEPTIME_MSEC 2000

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Define Actuators:
  //MotorStepperRotate* stepper = new MotorStepperRotate(HBRIDGE_PIN1, HBRIDGE_PIN2, HBRIDGE_PIN3, HBRIDGE_PIN4, STEPPER_RESOLUTION);
  MotorStepperRotateI2C* stepper = new MotorStepperRotateI2C(STEPPER_NR, STEPPER_RESOLUTION, MAX_CYCLES_PER_SECOND);

  //** Define Input
  // Variable input sets the rotation speed of the motor.
  VariableInput* poti = new VariableInput(VARIABLE_INPUT_PIN);

  //** Define logic with condition and relation
  // No condition (NULL) because the relation is always active
  Relation1to1* relation = new Relation1to1(NULL, stepper, poti);
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