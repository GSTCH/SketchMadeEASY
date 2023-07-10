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
/* Adafruit Motor Driver Shield V2 */
#define STEPPER_NR 2
/* 28BYJ-48 */
//#define STEPPER_RESOLUTION 32
//#define STEPPER_GEARRATIO 64

// Stepper motor:  Moons PG22L71.7
#define STEPPER_RESOLUTION 20
#define STEPPER_GEARRATIO 71

#define STEPPER_RPM 5
#define STEPPER_MIN_ANGLE 0
#define STEPPER_MAX_ANGLE 360

#define HOME_LIMITSWITCH_PIN 41
#define HOME_LIMITSWITCH_MODE smPullUpExternal

#define ANGLE_STEPWIDTH_DEGREE 10
#define STEPWIDTH_MSEC 1000

void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("ServoStepperPositionI2C Test");
#endif

  //ServoStepperPositionI2C* stepper = new ServoStepperPositionI2C(STEPPER_NR, STEPPER_RESOLUTION, STEPPER_GEARRATIO, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RPM, spForward, HOME_LIMITSWITCH_PIN, HOME_LIMITSWITCH_MODE);
  //ServoStepperPositionI2C* stepper = new ServoStepperPositionI2C(STEPPER_NR, STEPPER_RESOLUTION, STEPPER_GEARRATIO, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RPM, spBackward, HOME_LIMITSWITCH_PIN, HOME_LIMITSWITCH_MODE);
  ServoStepperPositionI2C* stepper = new ServoStepperPositionI2C(STEPPER_NR, STEPPER_RESOLUTION, STEPPER_GEARRATIO, STEPPER_MIN_ANGLE, STEPPER_MAX_ANGLE, STEPPER_RPM, spNone, 0, HOME_LIMITSWITCH_MODE);
  
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
