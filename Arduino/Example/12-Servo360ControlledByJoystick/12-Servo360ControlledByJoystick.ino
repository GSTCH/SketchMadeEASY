//*****************************************************************
//* Example 12-Servo360 controlled by a Joystick(Axis)
//*
//* Servo 360°, the rotation speed and direction is controlled by a joystick
//*
//* Hardware:
//* - Servo 360° 
//* - Analog joystick with 10kOhm potentiometer
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
//*****************************************************************

#include <Easy.h>

//*****************************************************************
#define SERVO360_PIN 10
#define JOYSTICK_AXIS_PIN A10 // y=A9, x=A10

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Define Actuators:
  // Various types of servo control are supported. The main reason is a conflict of the timer interrupt, 
  // e.g. Log via Serial0 and MotorServoT1 is not possible at the same time. Uncumment the line of your 
  // choice.
  // Servo needs a PWM ouput pin. 
  //MotorServo360T1* servo360 = new MotorServo360T1(SERVO360_PIN);
  MotorServo360T2* servo360 = new MotorServo360T2(SERVO360_PIN);
  //MotorServo360Pwm* servo360 = new MotorServo360Pwm(SERVO360_PIN); //  has no INT conflict but work only with UNO R3 

  //** Define Input
  // joystickAxis is like a potentiometer but its value is from minus over 0 to plus.
  // No Inverter is therefore required to change the direction of rotation.
  JoystickAxis* xAxis = new JoystickAxis(JOYSTICK_AXIS_PIN, false);

  //** Define logic with condition and relation
  // No condition (NULL) because the relation is always active
  Relation1to1* relationServo = new Relation1to1( NULL, servo360, xAxis );
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