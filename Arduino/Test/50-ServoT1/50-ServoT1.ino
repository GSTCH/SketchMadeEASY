//*****************************************************************
// Test for servo using timer interrupt 1
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
#define SERVO_PIN 9
#define SERVO_ANGLE_MIN 0
#define SERVO_ANGLE_MAX 180
#define ANGLE_STEPWIDTH_DEGREE 10
#define STEPWIDTH_MSEC 1000

void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("ServoT1 Test");
#endif

  ServoT1* servo = new ServoT1(SERVO_PIN, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX);

  IteratorValue* iteratorValue = new IteratorValue(servo->getMinAngle(), servo->getMaxAngle(), ANGLE_STEPWIDTH_DEGREE, STEPWIDTH_MSEC, cmMin2Max2Min);

  Relation1to1* relationServoOff = new Relation1to1(NULL, servo, iteratorValue);
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
