//*****************************************************************
//* Test for motor controlled by L298:
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
// Parameter Motor
#define MOTOR_SPEEDPIN_A 10
#define MOTOR_DIRECTIONPIN_A 12
#define MOTOR_SPEEDPIN_B 11
#define MOTOR_DIRECTIONPIN_B 13
#define MOTOR_SPEED_STEPWIDTH 10
#define STEPWIDTH_MSEC 1000

void setup()
{
    //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("MotorL298 Test");
#endif

  // Create actuator motor L298 (A, to use B change _A to _B)
  MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN_A, MOTOR_SPEEDPIN_A);

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
