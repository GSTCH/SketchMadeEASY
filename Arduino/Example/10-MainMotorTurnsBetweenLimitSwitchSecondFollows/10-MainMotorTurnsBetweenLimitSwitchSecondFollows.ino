//*****************************************************************
//* Example 10-Main Motor turns between limit switch, second follows
//*
//* Two motors, one motor toggles between limit switches, the other
//* follows and turn in same direction. Main switch to start/stop.
//*
//* Hardware:
//* - 2 DC motor
//* - Shield(s) to control motors
//* - Potentiometer 10kOhm
//* - Switch On/Off
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
// Parameter Master Motor
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
// Parameter MainSwitch
#define MAIN_SWITCH_PIN 14
// Parameter variable Input
#define VARIABLE_INPUT_PIN A0
// ToggleSwitch
#define DIRECTION_PIN1 43
#define DIRECTION_PIN2 41

//***************************************************************************************************************
void setup() {
  //((*** Initialize: Configure your sketch here....

  //** Define Actuators:
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  MotorL9110* motorFollower = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  MotorI2C* motorLeader = new MotorI2C(MOTOR_NUMBER);

  //** Define Input
  // Main switch to start/stop all.
  Switch2Position* mainSwitch = new Switch2Position(MAIN_SWITCH_PIN);

  // Switch knows the value Pos1 and Pos2. The value changes depending on two signal.
  // This makes it possible to define motor direction (when value change).
  ToggleSwitch* toggleSwitch = new ToggleSwitch(DIRECTION_PIN1, DIRECTION_PIN2);

  // Create variable input, defines speed
  VariableInput* motorSpeed = new VariableInput(VARIABLE_INPUT_PIN);
  // To turn backward an inverter changes the sign of the variable input value
  Inverter* inverter = new Inverter(motorSpeed);

  //** Define logic with condition and relation
  // Define direction when signal 1 (limit switch 1 pressed). An ActuatorCollection is used because more than one Actuator depends
  // on the same condition. Because the input is assigned into the ActuatorCollection, the value is NULL into the Relation.
  LogicCondition* motorDirection1Condition = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, toggleSwitch, OpEQ, ToggleSwitch::Pos2);
  ActuatorCollection* actuatorCollectionMotorDirection1 = new ActuatorCollection(motorLeader, motorSpeed, motorFollower, motorSpeed);
  Relation1to1* relationMotorDirection1 = new Relation1to1(motorDirection1Condition, actuatorCollectionMotorDirection1, NULL);

  // Define direction when signal 2 (limit switch 2 pressed). An ActuatorCollection is used because more than one Actuator depends
  // on the same condition. Because the input is assigned into the ActuatorCollection, the value is NULL into the Relation.
  LogicCondition* motorDirection2Condition = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, toggleSwitch, OpEQ, ToggleSwitch::Pos1);
  ActuatorCollection* actuatorCollectionMotorDirection2 = new ActuatorCollection(motorLeader, inverter, motorFollower, inverter);
  Relation1to1* relationMotorDirection2 = new Relation1to1(motorDirection2Condition, actuatorCollectionMotorDirection2, NULL);

  // Define stop all, when switch is off
  CompareCondition* motorStopCondition = new CompareCondition(mainSwitch, OpEQ, Switch2Position::Off);
  ActuatorCollection* actuatorCollectionMotorStop = new ActuatorCollection(motorLeader, FixValue::Off(), motorFollower, FixValue::Off());
  Relation1to1* relationMotorStop = new Relation1to1(motorStopCondition, actuatorCollectionMotorStop, NULL);
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
