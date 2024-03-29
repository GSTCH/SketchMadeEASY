//*****************************************************************
//* Test for CrawlerSteering
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
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
#define JOYSTICK_XAXIS_PIN A10
#define JOYSTICK_YAXIS_PIN A9

#define SERVO360_PIN 10
#define MOTOR_PINA1 44
#define MOTOR_PINB1 46
#define MOTOR_PINA2 11
#define MOTOR_PINB2 12

#define MOTOR_NR 2

void setup() {

//((*** Initialize: Configure your sketch here...
#ifdef LOG_SETUP
  GetLog()->printf("CrawlerSteering Test");
#endif

  JoystickAxis* xAxis = new JoystickAxis(JOYSTICK_XAXIS_PIN, false);
  JoystickAxis* yAxis = new JoystickAxis(JOYSTICK_YAXIS_PIN, false );

  MotorServo360T1* motorLeft = new MotorServo360T1(SERVO360_PIN);
  //MotorI2C* motorRight = new MotorI2C(MOTOR_NR);
  //MotorL9110* motorRight = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  MotorL9110* motorRight = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);

  CrawlerSteering* crawlerSteering = new CrawlerSteering(NULL, motorLeft, motorRight, xAxis, yAxis, 25);
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required

#ifdef LOG_LOOP_DEBUG
  GetLog()->println("Loop");
#endif

  ControlManagerFactory::GetControlManager()->Loop();

  delay(5);
}
