//*****************************************************************
// Test for a servo controilles by a Adafruit servo shield (I2C)
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
/* ULN2003 */
/*
#define STEPPER_PIN1 8
#define STEPPER_PIN2 9
#define STEPPER_PIN3 10
#define STEPPER_PIN4 11
*/
/* Frugo Robotic Shield */
#define STEPPER_PIN1 12
#define STEPPER_PIN2 10
#define STEPPER_PIN3 13
#define STEPPER_PIN4 11

/* 28BYJ-48 */
#define STEPPER_RESOLUTION 32
#define STEPPER_GEARRATIO 64

#define STEPPER_RPM 5
#define STEPPER_MIN_ANGLE 0
#define STEPPER_MAX_ANGLE 360

#define HOME_LIMITSWITCH_PIN 2

#define ANGLE_STEPWIDTH_DEGREE 10
#define STEPWIDTH_MSEC 1000

void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("ServoStepperPositionI2C Test");
#endif

  //** Shields: ULN2003, L9110S:
  //ServoStepperPosition* stepper = new ServoStepperPosition(STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4, STEPPER_RPM, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RESOLUTION, spForward, HOME_LIMITSWITCH_PIN, miHalf4Wire);
  //ServoStepperPosition* stepper = new ServoStepperPosition(STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4, STEPPER_RPM, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RESOLUTION, spBackward, HOME_LIMITSWITCH_PIN, miHalf4Wire);
  ServoStepperPosition* stepper = new ServoStepperPosition(STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4, STEPPER_RPM, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RESOLUTION, spNone, 0, miHalf4Wire);

  
  IteratorValue* iteratorValue = new IteratorValue(stepper->getMinAngle(), stepper->getMaxAngle(), ANGLE_STEPWIDTH_DEGREE, STEPWIDTH_MSEC, cmMin2Max2Min);

  Relation1to1* relationServoOff = new Relation1to1(NULL, stepper, iteratorValue);
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
