//*****************************************************************
//* Example 05-Motor Left/Off/Right
//*
//* Motor fix speed, controlled by switch (L-0-R). Motor turn 100% 
//* of the maximum speed forward and into the other direction (backwards) 80%. 
//*
//* Hardware:
//* - Shield to control motor
//* - DC motor 
//* - Switch with position (1-0-1)
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard 
//* with different motor shield types.
//*
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

#include <Easy.h>

//*****************************************************************
// Parameter Motor L298
#define MOTOR_SPEEDPIN 10
#define MOTOR_DIRECTIONPIN 12
// Parameter Motor L9110
#define MOTOR_PINA1 44
#define MOTOR_PINB1 46
#define MOTOR_PINA2 11
#define MOTOR_PINB2 12
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

  //** Create actuator:
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorI2C* motor = new MotorI2C(MOTOR_NUMBER);

  //** Create input:
  // Switch used by condition in the logic.
  Switch3Position* motorSwitch = new Switch3Position(MOTOR_SWITCH_FORWARDPIN, MOTOR_SWITCH_BACKWARDPIN);

  //** Define logic with conditions and relations
  // Define relation when switch is at position 1 --> Turn forward with fix speed
  CompareCondition* motorForwardCondition = new CompareCondition(motorSwitch, OpEQ, Switch3Position::Pos1);
  Relation1to1* relationMotorForward = new Relation1to1(motorForwardCondition, motor, FixValue::Percent(FIX_VALUE_FORWARDSPEED_SPEED));

  // Define relation when switch is at position 2 --> Turn backward with fix speed
  CompareCondition* motorBackwardCondition = new CompareCondition(motorSwitch, OpEQ, Switch3Position::Pos2);
  Relation1to1* relationMotorBackward = new Relation1to1(motorBackwardCondition, motor, FixValue::Percent(FIX_VALUE_BACKWARDSPEED_SPEED));

  // Define relation when switch is at position 0 --> stopped
  CompareCondition* motorStopCondition = new CompareCondition(motorSwitch, OpEQ, Switch3Position::PosMid);
  Relation1to1* relationMotorStop = new Relation1to1(motorStopCondition, motor, FixValue::Off());
// ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
