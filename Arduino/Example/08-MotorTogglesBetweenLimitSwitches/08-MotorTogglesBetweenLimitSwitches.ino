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
#define MOTOR_NUMBER 2
// ToggleSwitch
#define DIRECTION_PIN1 43  // NANO_DIRECTION_PIN1 5
#define DIRECTION_PIN2 41  // NANO_DIRECTION_PIN2 6
// Parameter variable Input
#define VARIABLE_INPUT_PIN A0

void setup()
{
   //((*** Initialize: Configure your sketch here....
   
  //** Create actuator:
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  MotorI2C* motor = new MotorI2C(MOTOR_NUMBER);

  //** Create input:
  // Create variable input, defines speed
  VariableInput* motorSpeed = new VariableInput(VARIABLE_INPUT_PIN);
  // To turn backward an inverter changes the sign of the variable input value
  Inverter* inverter = new Inverter(motorSpeed);

  // Switch knows the value Pos1 and Pos2. The value changes depending on two signal.
  // This makes it possible to define motor direction (when value change).
  ToggleSwitch* toggleSwitch = new ToggleSwitch(DIRECTION_PIN1, DIRECTION_PIN2);

  //** Define logic with conditions and relations
  // Define direction when signal 1 (limit switch 1 pressed)  
  CompareCondition* motorDirection1Condition = new CompareCondition(toggleSwitch, OpEQ, ToggleSwitch::Pos2);
  Relation1to1* relationMotorDirection1 = new Relation1to1(motorDirection1Condition, motor, motorSpeed);

  // Define direction when signal 2 (limit switch 2 pressed)
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

