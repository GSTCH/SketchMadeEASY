//*****************************************************************
//* Example 07-Motor variable speed, direction and main switch
//*
//* Motor variable speed, controlled by switch (L-0-R). Additional main switch.
//*
//* Hardware:
//* - Shield to control motor
//* - DC motor
//* - Switch with position 1-0-1
//* - Potentiometer 10kOhm
//* - Switch with position 1-0
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
// Parameter Motor
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
// Parameter MainSwitch
#define MAIN_SWITCH_PIN 39
// Parameter of Switch
#define MOTOR_SWITCH_FORWARDPIN 36
#define MOTOR_SWITCH_BACKWARDPIN 37
// Parameter variable Input
#define VARIABLE_INPUT_PIN A0

void setup() {
  //((*** Initialize: Configure your sketch here....

  //** Create actuator:
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  //MotorI2C* motor = new MotorI2C(MOTOR_NUMBER);

  //** Create input:
  // Create input direction switch
  Switch3Position* motorSwitch = new Switch3Position(MOTOR_SWITCH_FORWARDPIN, MOTOR_SWITCH_BACKWARDPIN);

  // Create input main switch
  Switch2Position* mainSwitch = new Switch2Position(MAIN_SWITCH_PIN);

  // Create variable input, defines speed
  VariableInput* motorSpeed = new VariableInput(VARIABLE_INPUT_PIN);
  // To turn backward an inverter changes the sign of the variable input value
  Inverter* inverter = new Inverter(motorSpeed);

  //** Define logic with conditions and relations
  // Define relation when motor turns forward
  LogicCondition* motorForwardCondition = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, motorSwitch, OpEQ, Switch3Position::Pos1);
  Relation1to1* relationMotorForward = new Relation1to1(motorForwardCondition, motor, motorSpeed);

  // Define relation when motor turns backward
  LogicCondition* motorBackwardCondition = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, motorSwitch, OpEQ, Switch3Position::Pos2);
  Relation1to1* relationMotorBackward = new Relation1to1(motorBackwardCondition, motor, inverter);

  // Define relation when motor stops
  LogicCondition* motorStopCondition = new LogicCondition(mainSwitch, OpEQ, Switch2Position::Off, LgOR, motorSwitch, OpEQ, Switch3Position::PosMid);
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
