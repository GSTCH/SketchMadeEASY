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

// Uncomment the defines #define PLOT_ENCODERMOTOR or #define PLOT_ROTARYENCODER 
// ino the library file "Src\Kernel\BuildDefinition.h" to see plot into the Ardino IDE 

#include <Easy.h>

//*****************************************************************
// Parameter MotorShield
#define MOTOR_PINA1 44
#define MOTOR_PINB1 46
#define MOTOR_PINA2 11
#define MOTOR_PINB2 12

// Parameter for RotaryEncoder
#define ENCA 3 // (use a interrupt when RISING, read doc to attachInterupt() to get usable pins)
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
  EncoderMotorL9110* encoderMotor = new EncoderMotorL9110(MOTOR_PINA2, MOTOR_PINB2, ENCA, ENCB, PPR, GEAR_RATIO, 0);
  
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
