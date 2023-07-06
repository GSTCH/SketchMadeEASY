//*****************************************************************
//* Model 04 - Meccano model MP154 simpe robot (plan from MWMailOrder)
//*
//* Robotic arm with 5 motors. Switch to change mode. 3 modes are supported:
//* - Manual: (L)-0-(R) switch per motor,  potentionmeter defines speed per motor
//* - Bluetooth/App built with AppInventor
//* - RemoteControl FlySky FS-I6X
//*
//* Hardware:
//* - Arduino Mega 2560 R3 is recommended,
//* - Adafruit MotorShield v2
//* - Prototyp/Screw shield (Optional)
//* - 1 switch with 3 position 1-0-1 
//* - 5 switch with 3 position (1)-0-(1) 
//* - 5 Potentiometer 10kOhm
//* - HC06 Bluetooth shield
//* - FlySky FS-I6X sender
//* - FlySky FS-iA6B receiver
//* 
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

// Parameter for motor shields 
#define I2CBUS_ADRESS_MOTORSHIELD1 0x60
#define I2CBUS_ADRESS_MOTORSHIELD2 0x61
#define MOTORa_I2C_NUMBER 1
#define MOTORb_I2C_NUMBER 2
#define MOTORc_I2C_NUMBER 3
#define MOTORd_I2C_NUMBER 4
#define MOTORe_I2C_NUMBER 1
// Parameter motor speed
#define SPEED_MOTORa_PIN A0
#define SPEED_MOTORb_PIN A8
#define SPEED_MOTORc_PIN A11
#define SPEED_MOTORd_PIN A3
#define SPEED_MOTORe_PIN A4
// Parameter mode selection switch
#define SWITCH_MODESELECTION_HANDY_PIN 29
#define SWITCH_MODESELECTION_FLYSKY_PIN 30
// Parameter for MotorControlSwitch (manually mode)  
#define SWITCH_MOTORa_DIRECTION1 32
#define SWITCH_MOTORa_DIRECTION2 33
#define SWITCH_MOTORb_DIRECTION1 35
#define SWITCH_MOTORb_DIRECTION2 36
#define SWITCH_MOTORc_DIRECTION1 38
#define SWITCH_MOTORc_DIRECTION2 39
#define SWITCH_MOTORd_DIRECTION1 41
#define SWITCH_MOTORd_DIRECTION2 42
#define SWITCH_MOTORe_DIRECTION1 48
#define SWITCH_MOTORe_DIRECTION2 49

void setup() {
  //((*** Initialize: Configure your sketch here....

  //** Common elements
  // Define mode switch
  Switch3Position* modeSelectionSwitch = new Switch3Position(SWITCH_MODESELECTION_HANDY_PIN, SWITCH_MODESELECTION_FLYSKY_PIN);

  // Define motor switches
  Switch3Position* switchMotorA = new Switch3Position(SWITCH_MOTORa_DIRECTION1, SWITCH_MOTORa_DIRECTION2);
  Switch3Position* switchMotorB = new Switch3Position(SWITCH_MOTORb_DIRECTION1, SWITCH_MOTORb_DIRECTION2);
  Switch3Position* switchMotorC = new Switch3Position(SWITCH_MOTORc_DIRECTION1, SWITCH_MOTORc_DIRECTION2);
  Switch3Position* switchMotorD = new Switch3Position(SWITCH_MOTORd_DIRECTION1, SWITCH_MOTORd_DIRECTION2);
  Switch3Position* switchMotorE = new Switch3Position(SWITCH_MOTORe_DIRECTION1, SWITCH_MOTORe_DIRECTION2);

  // Define speeds 
  FixValue* stopSpeed = FixValue::Off(); // Spare RAM: define once, use multiple times

  VariableInput* motorSpeedForwardA = new VariableInput(SPEED_MOTORa_PIN);
  Inverter* motorSpeedBackwardA = new Inverter(motorSpeedForwardA);

  VariableInput* motorSpeedForwardB = new VariableInput(SPEED_MOTORb_PIN);
  Inverter* motorSpeedBackwardB = new Inverter(motorSpeedForwardB);

  VariableInput* motorSpeedForwardC = new VariableInput(SPEED_MOTORc_PIN);
  Inverter* motorSpeedBackwardC = new Inverter(motorSpeedForwardC);

  VariableInput* motorSpeedForwardD = new VariableInput(SPEED_MOTORd_PIN);
  Inverter* motorSpeedBackwardD = new Inverter(motorSpeedForwardD);

  VariableInput* motorSpeedForwardE = new VariableInput(SPEED_MOTORe_PIN);
  Inverter* motorSpeedBackwardE = new Inverter(motorSpeedForwardE);

  // Define remote controls
  FlySky* flySky = new FlySky(scHard1);
  AppInventor* appInventor = new AppInventor(scHard3);

  // Define actuators
  MotorI2C* motorA = new MotorI2C(MOTORa_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  MotorI2C* motorB = new MotorI2C(MOTORb_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  MotorI2C* motorC = new MotorI2C(MOTORc_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  MotorI2C* motorD = new MotorI2C(MOTORd_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);  
  MotorI2C* motorE = new MotorI2C(MOTORe_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD2);

  //** Define logic with relations and conditions

  //* FlySky
  CompareCondition* conditionControledByFlySky = new CompareCondition(modeSelectionSwitch, OpEQ, Switch3Position::Pos1);
  ActuatorCollection* actuatorCollectionFlySky = new ActuatorCollection(
    motorA, flySky->GetControl(rcJoystick2X),
    motorB, flySky->GetControl(rcJoystick1X),
    motorC, flySky->GetControl(rcJoystick1Y),
    motorD, flySky->GetControl(rcJoystick2Y),
    motorE, flySky->GetControl(rcSwC));
  Relation1to1* relationFlySky = new Relation1to1(conditionControledByFlySky, actuatorCollectionFlySky, NULL);

  //* AppInventor
  CompareCondition* conditionControledByAppInventor = new CompareCondition(modeSelectionSwitch, OpEQ, Switch3Position::Pos2);
  ActuatorCollection* actuatorCollectionAppInventor = new ActuatorCollection(
    motorA, appInventor->GetControl(rcJoystick2X),
    motorB, appInventor->GetControl(rcJoystick1X),
    motorC, appInventor->GetControl(rcJoystick1Y),
    motorD, appInventor->GetControl(rcJoystick2Y),
    motorE, appInventor->GetControl(rcSwC));
  Relation1to1* relationAppInventor = new Relation1to1(conditionControledByAppInventor, actuatorCollectionAppInventor, NULL);

  //* Manual mode
  // Motor A
  defineMotorWithSwitchInModeManually(motorA, modeSelectionSwitch, switchMotorA, motorSpeedForwardA, motorSpeedBackwardA, stopSpeed);
  // Motor B
  defineMotorWithSwitchInModeManually(motorB, modeSelectionSwitch, switchMotorB, motorSpeedForwardB, motorSpeedBackwardB, stopSpeed);
  // Motor C
  defineMotorWithSwitchInModeManually(motorC, modeSelectionSwitch, switchMotorC, motorSpeedForwardC, motorSpeedBackwardC, stopSpeed);
  // Motor D
  defineMotorWithSwitchInModeManually(motorD, modeSelectionSwitch, switchMotorD, motorSpeedForwardD, motorSpeedBackwardD, stopSpeed);
  // Motor E
  defineMotorWithSwitchInModeManually(motorE, modeSelectionSwitch, switchMotorE, motorSpeedForwardE, motorSpeedBackwardE, stopSpeed);
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
// All switches have the same logic. To make the code shorter and better maintainable, this fuction defines
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
