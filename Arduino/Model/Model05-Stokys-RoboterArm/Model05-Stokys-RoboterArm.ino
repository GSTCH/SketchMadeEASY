//*****************************************************************
//* Model 05 - Stokys roboter arm
//* (Same control as model 04, but motor poti 5 has been used for a servo.)
//*
//* Robotic arm with 4 motors and a servo. 
//* Switch to change mode. 3 modes are supported:
//* - Manual: - (L)-0-(R) switch per motor,  potentionmeter defines speed per motor
//*           - Potentionmeter to define the servo position
//* - Bluetooth/App built with AppInventor
//* - RemoteControl FlySky FS-I6X
//*
//* Hardware:
//* - Arduino Mega 2560 R3 is recommended,
//* - Adafruit MotorShield v2
//* - Adafruit 16-Channel 12-bit PWM/Servo Shield-I2C
//* - Prototyp/Screw shield (Optional)
//* - 1 switch with 3 position 1-0-1
//* - 4 switch with 3 position (1)-0-(1)
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

#define LOG
#define LOG_LOOP
#include <Easy.h>

//*****************************************************************

// Parameter for motor shields
#define I2CBUS_ADRESS_MOTORSHIELD1 0x60
#define I2CBUS_ADRESS_MOTORSHIELD2 0x61
#define MOTORa_I2C_NUMBER 1
#define MOTORb_I2C_NUMBER 2
#define MOTORc_I2C_NUMBER 3
#define MOTORd_I2C_NUMBER 4
// Parameter motor speed
#define SPEED_MOTORa_PIN A15
#define SPEED_MOTORb_PIN A14
#define SPEED_MOTORc_PIN A13
#define SPEED_MOTORd_PIN A12
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
//Servo Parameters
#define SERVO_POSITION_PIN A11
#define SERVO_NR 15
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 90

void setup() {
  //((*** Initialize: Configure your sketch here....
  GetLog()->println("Setup");

  //** Common elements

  // Define actuators
  MotorI2C* motorA = new MotorI2C(MOTORa_I2C_NUMBER);
  MotorI2C* motorB = new MotorI2C(MOTORb_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  MotorI2C* motorC = new MotorI2C(MOTORc_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  MotorI2C* motorD = new MotorI2C(MOTORd_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);

  ServoI2C* servo = new ServoI2C(SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_NR);
  
  // Define mode switch
  Switch3Position* modeSelectionSwitch = new Switch3Position(SWITCH_MODESELECTION_HANDY_PIN, SWITCH_MODESELECTION_FLYSKY_PIN);

  // Define motor switches
  Switch3Position* switchMotorA = new Switch3Position(SWITCH_MOTORa_DIRECTION1, SWITCH_MOTORa_DIRECTION2);
  Switch3Position* switchMotorB = new Switch3Position(SWITCH_MOTORb_DIRECTION1, SWITCH_MOTORb_DIRECTION2);
  Switch3Position* switchMotorC = new Switch3Position(SWITCH_MOTORc_DIRECTION1, SWITCH_MOTORc_DIRECTION2);
  Switch3Position* switchMotorD = new Switch3Position(SWITCH_MOTORd_DIRECTION1, SWITCH_MOTORd_DIRECTION2);

  // Define speeds
  FixValue* stopSpeed = FixValue::Off();  // Spare RAM: define once, use multiple times

  VariableInput* motorSpeedForwardA = new VariableInput(SPEED_MOTORa_PIN);
  Inverter* motorSpeedBackwardA = new Inverter(motorSpeedForwardA);

  VariableInput* motorSpeedForwardB = new VariableInput(SPEED_MOTORb_PIN);
  Inverter* motorSpeedBackwardB = new Inverter(motorSpeedForwardB);

  VariableInput* motorSpeedForwardC = new VariableInput(SPEED_MOTORc_PIN);
  Inverter* motorSpeedBackwardC = new Inverter(motorSpeedForwardC);

  VariableInput* motorSpeedForwardD = new VariableInput(SPEED_MOTORd_PIN);
  Inverter* motorSpeedBackwardD = new Inverter(motorSpeedForwardD);

  VariableInput* servoPosition = new VariableInput(SERVO_POSITION_PIN);

  // Define remote controls
  CompareCondition* flySkyEnabledCondition = new CompareCondition(modeSelectionSwitch, OpEQ, Switch3Position::Pos1);
  FlySky* flySky = new FlySky(scHard2, flySkyEnabledCondition);

  CompareCondition* appEnabledCondition = new CompareCondition(modeSelectionSwitch, OpEQ, Switch3Position::Pos2);
  AppInventor* app = new AppInventor(scHard3, appEnabledCondition);

  //** Define logic with relations and conditions

  //* Motor A:
  GetLog()->println("***MotorA");
  // Manual mode depends on motorSwitchA
  DependentInput* motorManualSpeedA = new DependentInput(switchMotorA,
                                                         stopSpeed,             // motor switch at Pos0/PosMid: Stop
                                                         motorSpeedForwardA,    // motor switch at Pos1 : Forward
                                                         motorSpeedBackwardA);  // motor switch at Pos2 : Backward

  // Input is in relation to the mode switch:
  DependentInput* inputMotorA = new DependentInput(
    // Switch define the index of input to use
    modeSelectionSwitch,
    // Mode selection switch Pos0/PosMid: Manual Mode with switch: True when greather than Pos1, is when Pos2
    motorManualSpeedA,
    // Mode selection switch Pos1: FlySky FS-I6X remote control
    flySky->getControl(rcJoystick1X),
    // Mode selection switch Pos2: HandyApp
    app->getControl(rcJoystick1X));

  // Define logic and link motor conditionless to the DepentInput
  Relation1to1* relationManualStopMotorA = new Relation1to1(NULL, motorA, inputMotorA);

  //* Motor B:
  GetLog()->println("***MotorB");
  // Same as motorB, to increase readability, the definiton is in a method.
  // This method is usable for all motors
  DefineMotor(modeSelectionSwitch, switchMotorB,
              motorSpeedForwardB, motorSpeedBackwardB, stopSpeed,
              flySky->getControl(rcJoystick1Y), app->getControl(rcJoystick1Y),
              motorB);

  //* Motor C:
  GetLog()->println("***MotorC");
  DefineMotor(modeSelectionSwitch, switchMotorC,
              motorSpeedForwardC, motorSpeedBackwardC, stopSpeed,
              flySky->getControl(rcJoystick2X), app->getControl(rcJoystick2X),
              motorC);

  //* Motor D:
  GetLog()->println("***MotorD");
  DefineMotor(modeSelectionSwitch, switchMotorD,
              motorSpeedForwardD, motorSpeedBackwardD, stopSpeed,
              flySky->getControl(rcJoystick2Y), app->getControl(rcJoystick2Y),
              motorD);
  //* Servo:  
  GetLog()->println("***Servo"); 
  // The remote control has only 8 joystick axis. Servo position use a rotation knob 
   DependentInput* servoModePosition = new DependentInput(modeSelectionSwitch,
                                                         servoPosition, 
                                                         flySky->getControl(rcVrA),
                                                         app->getControl(rcVrA));
  Relation1to1* relationServo = new Relation1to1( NULL, servo, servoModePosition );

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
void DefineMotor(Input* aModeSelectionSwitch, Input* aSwitchMotor,
                 Input* aMotorSpeedForward, Input* aMotorSpeedBackward, Input* aStopSpeed,
                 Input* aFlySkyInput, Input* aAppInput,
                 Actuator* aMotor) {
  // Manual mode depends on motorSwitchA
  DependentInput* motorManualSpeed = new DependentInput(aSwitchMotor,
                                                        aStopSpeed,            // motor switch at Pos0/PosMid: Stop
                                                        aMotorSpeedForward,    // motor switch at Pos1 : Forward
                                                        aMotorSpeedBackward);  // motor switch at Pos2 : Backward

  // Input is in relation to the mode switch:
  DependentInput* inputMotor = new DependentInput(
    // Switch define the index of input to use
    aModeSelectionSwitch,
    // Mode selection switch Pos0/PosMid: Manual Mode with switch: True when greather than Pos1, is when Pos2
    motorManualSpeed,
    // Mode selection switch Pos1: FlySky FS-I6X remote control
    aFlySkyInput,
    // Mode selection switch Pos2: HandyApp
    aAppInput);

  // Define logic and link motor conditionless to the DepentInput
  Relation1to1* relationManualStopMotorA = new Relation1to1(NULL, aMotor, inputMotor);
}
