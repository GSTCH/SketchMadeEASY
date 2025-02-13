//*****************************************************************
//* Test for random eye movement
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2024 by Hans Rothenbühler. All right reserved.
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
//#define LOG_LOOP
#include <Easy.h>

//*****************************************************************
#define STEPWIDTH_HORIZONTAL_MSEC 149

// Parameter Servo1
#define SERVO_HORIZONTAL_NR 14
#define SERVO_HORIZONTAL_ANGLE_MIN 0
#define SERVO_HORIZONTAL_ANGLE_MAX 180
// Iterator do not drive full range
#define SERVO_HORIZONTAL_ANGLE_DRIVE_MIN 30
#define SERVO_HORIZONTAL_ANGLE_DRIVE_MAX 150
#define HORIZONTAL_ANGLE_STEPWIDTH_DEGREE 6 

// Parameter Servo2
#define SERVO_VERTICAL_NR 15
#define SERVO_VERTICAL_ANGLE_MIN 0
#define SERVO_VERTICAL_ANGLE_MAX 180
// Iterator do not drive full range
#define SERVO_VERTICAL_ANGLE_DRIVE_MIN 30
#define SERVO_VERTICAL_ANGLE_DRIVE_MAX 150
#define VERTICAL_ANGLE_STEPWIDTH_DEGREE 5

void setup() {
//((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Setup EyeSimulator Test");
#endif

  ServoI2C* servoHorizontal = new ServoI2C(SERVO_HORIZONTAL_ANGLE_MIN, SERVO_HORIZONTAL_ANGLE_MAX, SERVO_HORIZONTAL_NR);
  ServoI2C* servoVertical = new ServoI2C(SERVO_VERTICAL_ANGLE_MIN, SERVO_VERTICAL_ANGLE_MAX, SERVO_VERTICAL_NR);

  Input* horizontalValue = new IteratorValue(SERVO_HORIZONTAL_ANGLE_DRIVE_MIN, SERVO_HORIZONTAL_ANGLE_DRIVE_MAX, HORIZONTAL_ANGLE_STEPWIDTH_DEGREE, STEPWIDTH_HORIZONTAL_MSEC, cmMin2Max2Min);

  Relation* eyeSimulator = new EyeControl(NULL, horizontalValue,servoHorizontal, servoVertical);
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
