//*****************************************************************
//* Test for motor controlled by L9110:
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
#define MOTOR_PINA1 11
#define MOTOR_PINB1 12
#define MOTOR_PINA2 3
#define MOTOR_PINB2 4
#define MOTOR_SPEED_STEPWIDTH 10
#define STEPWIDTH_MSEC 1000

void setup()
{
    //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("MotorL9110 Test");
#endif

  // Create actuator motor L9110 (1, to use 2 change leading 1 of the defines to 2)
  MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);

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
