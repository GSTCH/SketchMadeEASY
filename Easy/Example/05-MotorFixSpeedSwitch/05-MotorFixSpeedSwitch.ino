//*****************************************************************
//* Example 05-Motor Left/Off/Right
//*
//* Motor fix speed, controlled by switch (L-0-R). Motor turn 100% 
//* of the maximum speed forward and into the other direction (backwards) 80%. 
//*
//* Hardware:
//* - L298 shield to control motor
//* - DC motor (Speed at PWM-PIN 10, Direction Pin=12)
//* - Switch with position (1-0-1) at PIN 6 and 8. Resistor of 10 kOhm at both Pin.
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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
//* Common infos:
//*
//*****************************************************************

#define LOG 
#define LOG_LOOP
#include <Easy.h>

//*****************************************************************
// Parameter Motor L298
#define MOTOR_SPEEDPIN 11
#define MOTOR_DIRECTIONPIN 12
// Parameter Motor L9110
#define MOTOR_PINA1 11
#define MOTOR_PINB1 12
#define MOTOR_PINA2 3
#define MOTOR_PINB2 4
// Parameter  I2C Motor
#define MOTOR_NUMBER 1
// Parameter of Switch
#define MOTOR_SWITCH_FORWARDPIN 36
#define MOTOR_SWITCH_BACKWARDPIN 37
// Parameter Fix Value
#define MOTOR_SPEED_MIN 0
#define MOTOR_SPEED_MAX 100
#define FIX_VALUE_FORWARDSPEED_SPEED 100
#define FIX_VALUE_BACKWARDSPEED_SPEED -80


void setup()
{
  //((*** Initialize: Configure your sketch here....

  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorI2C* motor = new MotorI2C(MOTOR_NUMBER);

  Switch3Position* motorSwitch = new Switch3Position(MOTOR_SWITCH_FORWARDPIN, MOTOR_SWITCH_BACKWARDPIN);

  CompareCondition* motorForwardCondition = new CompareCondition(motorSwitch, OpEQ, Switch3Position::Pos1);
  Relation1to1* relationMotorForward = new Relation1to1(motorForwardCondition, motor, FixValue::Percent(FIX_VALUE_FORWARDSPEED_SPEED));

  CompareCondition* motorBackwardCondition = new CompareCondition(motorSwitch, OpEQ, Switch3Position::Pos2);
  Relation1to1* relationMotorBackward = new Relation1to1(motorBackwardCondition, motor, FixValue::Percent(FIX_VALUE_BACKWARDSPEED_SPEED));

  CompareCondition* motorStopCondition = new CompareCondition(motorSwitch, OpEQ, Switch3Position::PosMid);
  Relation1to1* relationMotorStop = new Relation1to1(motorStopCondition, motor, FixValue::Off());
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

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
