//*****************************************************************
// Test for 360°-servo works with modified PWM signal. 
//* Does only works one Arduino UNO R3, PIN9 or PIN10
//* Advantage: Log possible on Serial0.
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
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

#define LOG 
#define LOG_LOOP
#include <Easy.h>

//*****************************************************************
#define SERVO360_PIN 9
#define MOTOR_SPEED_STEPWIDTH 10
#define STEPWIDTH_MSEC 1000

void setup()
{
     //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Servo360PWM Test");
#endif

  // Create input servo 360 (uses Timer 2, this prefent conflicts e.g. with serial0)
  MotorServo360Pwm* motor = new MotorServo360Pwm(SERVO360_PIN);

  IteratorValue* iteratorValue = new IteratorValue(-motor->getMaxSpeed(), motor->getMaxSpeed(), MOTOR_SPEED_STEPWIDTH, STEPWIDTH_MSEC, cmMin2Max2Min);
  Relation1to1* relationServoOff = new Relation1to1(NULL, motor, iteratorValue);
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