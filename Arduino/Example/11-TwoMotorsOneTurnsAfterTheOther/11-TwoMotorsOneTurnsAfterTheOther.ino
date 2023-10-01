//*****************************************************************
//* Example 11-Two motors, one turns after the other
//*
//* Two motors, one movement after the other. First toggles between limit switches.
//* Second motor turns some seconds when the first motor is at a end position.
//* When the seconds motors stops, first motor start with inverted direction.
//*
//* Hardware:
//* - 2 DC motor
//* - Shield(s) to control motors
//* - Potentiometer 10kOhm
//* - Switch On/Off
//*
//* The pins are for the Arduino Mega 2560 test board, on which all 
//* tests and examples are possible. Adjust the pins depending on 
//* your board.
//*
//* In the directory with the example are picture of the breadboard.
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
#define MOTOR_PINA1 10
#define MOTOR_PINB1 12
#define MOTOR_PINA2 44
#define MOTOR_PINB2 46
// Parameter I2C Motor
#define MOTOR_TOGGLE_NUMBER 2
#define MOTOR_TIMED_NUMBER 1
// Parameter MainSwitch
#define MAIN_SWITCH_PIN 39
// Parameter variable Input
#define VARIABLE_INPUT_PIN A0
// ToggleSwitch
#define DIRECTION_PIN1 43
#define DIRECTION_PIN2 41

// Parameters Monoflop end switch
#define MONOFLOP_LEFT_PIN 43
#define MONOFLOP_LEFT_HIGH_DELAY 5000
#define MONOFLOP_LEFT_LOW_DELAY 200
#define MONOFLOP_RIGHT_PIN 41
#define MONOFLOP_RIGHT_HIGH_DELAY 5000
#define MONOFLOP_RIGHT_LOW_DELAY 200

void setup() {
  //((*** Initialize: Configure your sketch here....
  //** Define Actuators:
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);  
  MotorI2C* motorToogles = new MotorI2C(MOTOR_TOGGLE_NUMBER);    // Create toggeling motor
  MotorI2C* motorTimed = new MotorI2C(MOTOR_TIMED_NUMBER);       // Create timed motor

  //** Define Input
  // Main switch to start/stop all.
  Switch2Position* mainSwitch = new Switch2Position(MAIN_SWITCH_PIN, smPullUpExternal);

  // Create the speed inputs
  VariableInput* motorSpeed = new VariableInput(VARIABLE_INPUT_PIN);
  Inverter* inverter = new Inverter(motorSpeed);
  FixValue* stopSpeed = FixValue::Off();

  // Define input monoflop to the limit switch, they turn the move of toggeling motor
  MonoFlop* monoFlopLeft = new MonoFlop(MONOFLOP_LEFT_PIN, MONOFLOP_LEFT_HIGH_DELAY, MONOFLOP_LEFT_LOW_DELAY, true, smPullUpExternal);
  MonoFlop* monoFlopRight = new MonoFlop(MONOFLOP_RIGHT_PIN, MONOFLOP_RIGHT_HIGH_DELAY, MONOFLOP_RIGHT_LOW_DELAY, false, smPullUpExternal);

  //** Define logic with condition and relation
  // ActuatorCollections are used because more than one actuator depends on the same condition.
  // Because each ActuatorCollectionItems has its own input, the Relation has no input (NULL).

  // Relation 1: Toggle motor reach limit switch left. Timed motor start for a defined time (backward).
  LogicCondition* monoFlopLeftHigh = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, monoFlopLeft, OpEQ, MonoFlop::StateHigh);
  ActuatorCollection* toggleMotorStopDelayMotorStartBackward = new ActuatorCollection(motorToogles, stopSpeed, motorTimed, inverter);
  Relation1to1* toggleMotorReachLimitSwitchLeft = new Relation1to1(monoFlopLeftHigh, toggleMotorStopDelayMotorStartBackward, NULL);

  // Relation 2: Timer duration ended, stop timed motor and start toggle motor in direction to right
  LogicCondition* monoFlopLeftHighTimerEnd = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, monoFlopLeft, OpEQ, MonoFlop::StateHighTimerEnd);
  ActuatorCollection* toggleMotorStopDelayMotorStartToRight = new ActuatorCollection(motorToogles, motorSpeed, motorTimed, stopSpeed);
  Relation1to1* timedMotorStopToggleMotorStartToRight = new Relation1to1(monoFlopLeftHighTimerEnd, toggleMotorStopDelayMotorStartToRight, NULL);


  // Relation 3: Toggle motor reach limit switch right. Timed motor start for a defined time (forward).
  LogicCondition* monoFlopRightHigh = new LogicCondition(mainSwitch, OpEQ, Switch2Position::On, LgAND, monoFlopRight, OpEQ, MonoFlop::StateHigh);
  ActuatorCollection* toggleMotorStopDelayMotorStartForward = new ActuatorCollection(motorToogles, stopSpeed, motorTimed, motorSpeed);
  Relation1to1* motorTimedStartRight = new Relation1to1(monoFlopRightHigh, toggleMotorStopDelayMotorStartForward, NULL);

  // Relation 4: Timer duration ended, stop timed motor and start toggle motor in direction to left
  LogicCondition* monoFlopRightHighTimerEnd = new LogicCondition(mainSwitch, OpEQ, 1, LgAND, monoFlopRight, OpEQ, MonoFlop::StateHighTimerEnd);
  ActuatorCollection* toggleMotorStopDelayMotorStartToLeft = new ActuatorCollection(motorToogles, inverter, motorTimed, stopSpeed);
  Relation1to1* timedMotorStopToggleMotorStartToLeft = new Relation1to1(monoFlopRightHighTimerEnd, toggleMotorStopDelayMotorStartToLeft, NULL);

  // Relation 5: Imidiately stop when main switch goes to low.
  CompareCondition* motorStopCondition = new CompareCondition(mainSwitch, OpEQ, Switch2Position::Off);
  // A different notation is used here. Up to 4 items are possible per constructor argument (as above),
  // this kind can contain any number of ActuatorCollectionItems.
  // A define is used for readability. It's not a const because they uses memory.
  #define ACTUATOR_COLLLECTION_ITEM_SIZE 2
  ActuatorCollectionItem** stopAllMotors = new ActuatorCollectionItem*[ACTUATOR_COLLLECTION_ITEM_SIZE];
  stopAllMotors[0] = new ActuatorCollectionItem(motorToogles, stopSpeed);
  stopAllMotors[1] = new ActuatorCollectionItem(motorTimed, stopSpeed);
  Relation1to1* relationStopAllMotors = new Relation1to1(motorStopCondition, stopAllMotors, ACTUATOR_COLLLECTION_ITEM_SIZE);
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
