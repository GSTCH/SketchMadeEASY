//*****************************************************************
//* Test for encoder motor controlled by L9110:
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//* Additional Log to Plot RotaryEncoder or EncoderMotor:
///*  --> uncomment "#define PLOT_ENCODERMOTOR" or "#define PLOT_ROTARYENCODER"
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
//#define PLOT_ENCODERMOTOR
//#define PLOT_ROTARYENCODER
#include <Easy.h>

//*****************************************************************
// Parameter MotorShield
#define MOTOR_PINA1 11
#define MOTOR_PINB1 12
#define MOTOR_PINA2 3
#define MOTOR_PINB2 4

// Parameter for RotaryEncoder
#define ENCA 3
#define ENCB 4
// Motor N20, n=100m 6V
#define PPR 7
#define GEAR_RATIO 150
// Motor GA25-370, n=126, 12V
/*
#define PPR 11 
#define GEAR_RATIO 34
*/
// Parameter TestCase
#define STEP_DURATION_MSEC 2000
#define MIN_ROTATIONSPEED -60
#define MAX_ROTATIONSPEED 60
#define STEP_AMOUNT 5

void setup()
{
    //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("EncoderMotorL298 Test");
#endif
  
  // Create actuator encoder motor
  EncoderMotorL9110* encoderMotor = new EncoderMotorL9110(MOTOR_PINA1, MOTOR_PINB1, ENCA, ENCB, PPR, GEAR_RATIO, 0);
  
  IteratorValue* iteratorValue = new IteratorValue(MIN_ROTATIONSPEED, MAX_ROTATIONSPEED, STEP_AMOUNT, STEP_DURATION_MSEC, cmMin2Max2Min);

  Relation1to1* relationServoOff = new Relation1to1(NULL, encoderMotor, iteratorValue);
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
