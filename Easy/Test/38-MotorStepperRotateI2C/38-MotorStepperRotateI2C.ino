//*****************************************************************
// Test for a stepper motor with controlled revolution speed.  
//* It uses the Adafruit motor shield V2 (I2C).
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

//***************************************************************************************************************
// Parameter Motor
#define STEPPER_NR 2

// Stepper motor:  28BYJ-48
#define STEPS_PER_ROTATION 32
#define GEAR_RATIO 64
#define STEPPER_RESOLUTION STEPS_PER_ROTATION * GEAR_RATIO
#define MAX_CYCLES_PER_SECOND 1000

#define MOTOR_SPEED_STEPWIDTH 10
#define STEPWIDTH_MSEC 1000

void setup()
{
    //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Stepper rotate motor I2C test ");
#endif

  // Create actuator stepper motor 
  MotorStepperRotateI2C* motor = new MotorStepperRotateI2C(STEPPER_NR, STEPPER_RESOLUTION, MAX_CYCLES_PER_SECOND, ssSingle);

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
