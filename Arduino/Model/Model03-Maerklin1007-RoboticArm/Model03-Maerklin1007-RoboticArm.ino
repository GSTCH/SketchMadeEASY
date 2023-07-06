//*****************************************************************
//* Model 03 - Maerklin model 1007 - RoboticArm with App
//*
//* Control to the robotics arm, from set 1007 of Marklin Metallbaukasten
//* Robotic arm with 4 motors. Switch to change control between bluetooth/app and (L)-0-(R) switches.
//* With the switches a potentionmeter defines speed for all motors.
//*
//* Hardware:
//* - 4 switch with 3 position (1)-0-(1) with 10kOhm Resitors
//* - 1 switch with 2 position 0-1 with 10kOhm Resitors
//* - Adafruit MotorShield v2
//* - Prototyp/Screw shield (Optional)
//* - Potentiometer 10kOhm
//* - HC06 Bluetooth shield
//*- Arduino Mega 2560 R3 is recommended, works at Uno R3 as well
//*****************************************************************
//* Sketch made Easy for Arduino - Arduino quick and easy
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
// Parameter motor shield
#define MOTORa_I2C_NUMBER 4
#define MOTORb_I2C_NUMBER 3
#define MOTORc_I2C_NUMBER 2
#define MOTORd_I2C_NUMBER 1
// Parameter control mode switch
#define SWITCH_MODESELECTION_PINAPP 13
// Parameter switch in manually control
#define SWITCH_MOTORa_PINFWD 2
#define SWITCH_MOTORa_PINRWD 3
#define SWITCH_MOTORb_PINFWD 4
#define SWITCH_MOTORb_PINRWD 5
#define SWITCH_MOTORc_PINFWD 6
#define SWITCH_MOTORc_PINRWD 7
#define SWITCH_MOTORd_PINFWD 8
#define SWITCH_MOTORd_PINRWD 9
#define SWITCH_RESISTOR_MODE smPullDownInternal // smPullUpExternal
// Parameter variable speed to all motors
#define VARIABLEINPUT_MOTORSPEED_PIN A0

#define FIX_VALUE_STOPSPEED_SPEED 0
#define SOFTSERIAL_RXPIN 5
#define SOFTSERIAL_TXPIN 6

void setup() {
  //((*** Initialize: Configure your sketch here....

  //** Define Actuators
  MotorI2C* motorA = new MotorI2C(MOTORa_I2C_NUMBER);
  MotorI2C* motorB = new MotorI2C(MOTORb_I2C_NUMBER);
  MotorI2C* motorC = new MotorI2C(MOTORc_I2C_NUMBER);
  MotorI2C* motorD = new MotorI2C(MOTORd_I2C_NUMBER);

  //** Define Input:
  // switches
  Switch3Position* switchMotorA = new Switch3Position(SWITCH_MOTORa_PINFWD, SWITCH_MOTORa_PINRWD, SWITCH_RESISTOR_MODE);
  Switch3Position* switchMotorB = new Switch3Position(SWITCH_MOTORb_PINFWD, SWITCH_MOTORb_PINRWD, SWITCH_RESISTOR_MODE);
  Switch3Position* switchMotorC = new Switch3Position(SWITCH_MOTORc_PINFWD, SWITCH_MOTORc_PINRWD, SWITCH_RESISTOR_MODE);
  Switch3Position* switchMotorD = new Switch3Position(SWITCH_MOTORd_PINFWD, SWITCH_MOTORd_PINRWD, SWITCH_RESISTOR_MODE);

  Switch2Position* modeSelectionSwitch = new Switch2Position(SWITCH_MODESELECTION_PINAPP, SWITCH_RESISTOR_MODE);

  // speeds
  VariableInput* motorSpeedForward = new VariableInput(VARIABLEINPUT_MOTORSPEED_PIN);
  Inverter* motorSpeedBackward = new Inverter(motorSpeedForward);
  FixValue* stopSpeed = FixValue::Off();

  //** Define RemoteControl
  AppInventor* appInventor = new AppInventor(scHard1);

  //modeSelectionSwitch=Pos1 RemoteControl
  ActuatorCollection* actuatorCollectionRemoteContol = new ActuatorCollection(
    motorA, appInventor->GetControl(rcJoystick2X),
    motorB, appInventor->GetControl(rcJoystick1X),
    motorC, appInventor->GetControl(rcJoystick1Y),
    motorD, appInventor->GetControl(rcJoystick2Y));

  CompareCondition* conditionSelectionSwitchApp = new CompareCondition(modeSelectionSwitch, OpEQ, Switch2Position::Pos1);
  Relation1to1* relationAppMotorA = new Relation1to1(conditionSelectionSwitchApp, actuatorCollectionRemoteContol, NULL);

  //modeSelectionSwitch=Pos0 Manual
  // Motor A
  defineMotorWithSwitchInModeManually(motorA, modeSelectionSwitch, switchMotorA, motorSpeedForward, motorSpeedBackward, stopSpeed);

  // Motor B
  defineMotorWithSwitchInModeManually(motorB, modeSelectionSwitch, switchMotorB, motorSpeedForward, motorSpeedBackward, stopSpeed);

  // Motor C
  defineMotorWithSwitchInModeManually(motorC, modeSelectionSwitch, switchMotorC, motorSpeedForward, motorSpeedBackward, stopSpeed);

  // Motor D
    defineMotorWithSwitchInModeManually(motorD, modeSelectionSwitch, switchMotorD, motorSpeedForward, motorSpeedBackward, stopSpeed);
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

//*****************************************************************
// All 4 switches have the same logic. To make the code shorter and better maintainable, this fuction defines
// the logic of a moto in manually mode.
void defineMotorWithSwitchInModeManually(Actuator* aMotor, Input* aModeSwitch, Input* aMotorSwitch,
                                       Input* aForwardSpeed, Input* aBackwardSpeed, Input* aStopSpeed) {
  // Motor stopped
  LogicCondition* conditionManualStopMotor = new LogicCondition(aModeSwitch, OpEQ, Switch2Position::Pos0,
                                                                LgAND,
                                                                aMotorSwitch, OpEQ, Switch3Position::Pos0);
  Relation1to1* relationManualStopMotor = new Relation1to1(conditionManualStopMotor, aMotor, aStopSpeed);

  // Motor forward
  LogicCondition* conditionManualForwardMotor = new LogicCondition(aModeSwitch, OpEQ, Switch2Position::Pos0,
                                                                   LgAND,
                                                                   aMotorSwitch, OpEQ, Switch3Position::Pos1);
  Relation1to1* relationManualForwardMotor = new Relation1to1(conditionManualForwardMotor, aMotor, aForwardSpeed);

  // Motor backward
  LogicCondition* conditionManualBackwardMotor = new LogicCondition(aModeSwitch, OpEQ, Switch2Position::Pos0,
                                                                    LgAND,
                                                                    aMotorSwitch, OpEQ, Switch3Position::Pos2);
  Relation1to1* relationManualBackwardMotor = new Relation1to1(conditionManualBackwardMotor, aMotor, aBackwardSpeed);
}
