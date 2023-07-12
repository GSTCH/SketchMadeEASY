//*****************************************************************
//* Example 17-Servo position in relation to a potentiometer
//*
//* Servo, the angled is controlled by a potentiometer
//*
//* Hardware:
//* - Servo at Pin 9
//* - Potentiometer with 10kOhm
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard.
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
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard 
//* with different motor shield types.
//*
//*****************************************************************

#include <Easy.h>

//*****************************************************************
// Parameter Servo
#define SERVO_PIN 9
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
// Parameter Potentiometer
#define VARIABLE_INPUT_PIN A0

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Define Actuators:
  // Different kind of servo control are supported, choose one of them by uncomment them
  ServoT2* servo = new ServoT2(SERVO_PIN, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
//ServoPwm* servo = new ServoPwm(SERVO_PIN, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
//ServoT1* servo = new ServoT1(SERVO_PIN, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

  //** Define Input
  VariableInput* poti = new VariableInput(VARIABLE_INPUT_PIN);

  //** Define logic with condition and relation
  Relation1to1* relationServo = new Relation1to1( NULL, servo, poti );
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