//*****************************************************************
//* Example 08-Motor toggles between (two) limit switches
//*
//* Motor with variable speed, toggles between two limit switches.
//*
//* Hardware:
//* - Shield to control motor
//* - DC motor
//* - Potentiometer 10kOhm
//* - Two limit switch 
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
#define MOTOR_PINA1 10
#define MOTOR_PINB1 12
#define MOTOR_PINA2 3
#define MOTOR_PINB2 4
// Parameter  I2C Motor
#define MOTOR_NUMBER 2
// ToggleSwitch
#define DIRECTION_PIN1 43  // NANO_DIRECTION_PIN1 5
#define DIRECTION_PIN2 41  // NANO_DIRECTION_PIN2 6
// Parameter variable Input
#define VARIABLE_INPUT_PIN A0

void setup()
{
   //((*** Initialize: Configure your sketch here....
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  MotorI2C* motor = new MotorI2C(MOTOR_NUMBER);

  VariableInput* motorSpeed = new VariableInput(VARIABLE_INPUT_PIN);
  Inverter* inverter = new Inverter(motorSpeed);

  ToggleSwitch* toggleSwitch = new ToggleSwitch(DIRECTION_PIN1, DIRECTION_PIN2);

  CompareCondition* motorDirection1Condition = new CompareCondition(toggleSwitch, OpEQ, ToggleSwitch::Pos2);
  Relation1to1* relationMotorDirection1 = new Relation1to1(motorDirection1Condition, motor, motorSpeed);

  CompareCondition* motorDirection2Condition = new CompareCondition(toggleSwitch, OpEQ, ToggleSwitch::Pos1);
  Relation1to1* relationMotorDirection2 = new Relation1to1(motorDirection2Condition, motor, inverter);
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

