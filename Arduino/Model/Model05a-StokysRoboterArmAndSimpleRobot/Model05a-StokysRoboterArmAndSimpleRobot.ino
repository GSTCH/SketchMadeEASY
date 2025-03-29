//*****************************************************************
//* Model 05a - Stokys roboter arm + Meccano simple robot
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
//* Using:
//* FlySky and Bluetooth does not work simultaneous. The position
//* of the mode during setup defines the created remoteControl.
//* After the setup middle is manual, and for RC it's always the
//* same position.
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
#define MOTORe_I2C_NUMBER 4
// Parameter motor speed
#define SPEED_MOTORa_PIN A10
#define SPEED_MOTORb_PIN A14
#define SPEED_MOTORc_PIN A13
#define SPEED_MOTORd_PIN A12
#define SPEED_MOTORe_PIN A11
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
//Servo Parameters
#define SERVO_POSITION_PIN A11
#define SERVO_NR 15
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 90


void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->println("Setup");
#endif

  // Define actuators
  Actuator* motorA = new MotorI2C(MOTORa_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  Actuator* motorB = new MotorI2C(MOTORb_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  Actuator* motorC = new MotorI2C(MOTORc_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  Actuator* motorD = new MotorI2C(MOTORd_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD1);
  Actuator* motorE = new MotorI2C(MOTORe_I2C_NUMBER, I2CBUS_ADRESS_MOTORSHIELD2);
  Actuator* servo = new ServoI2C(SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_NR);

  // Define mode switch
  Input* modeSelectionSwitch = new Switch3Position(SWITCH_MODESELECTION_HANDY_PIN, SWITCH_MODESELECTION_FLYSKY_PIN);

  // Define motor switches
#ifdef LOG
  GetLog()->println("SpeedMotor");
#endif
  Input* speedMotorA = new VariableInputSwitch(SPEED_MOTORa_PIN, SWITCH_MOTORa_DIRECTION1, SWITCH_MOTORa_DIRECTION2);
  Input* speedMotorB = new VariableInputSwitch(SPEED_MOTORb_PIN, SWITCH_MOTORb_DIRECTION1, SWITCH_MOTORb_DIRECTION2);
  Input* speedMotorC = new VariableInputSwitch(SPEED_MOTORc_PIN, SWITCH_MOTORc_DIRECTION1, SWITCH_MOTORc_DIRECTION2);
  Input* speedMotorD = new VariableInputSwitch(SPEED_MOTORd_PIN, SWITCH_MOTORd_DIRECTION1, SWITCH_MOTORd_DIRECTION2);
  Input* speedMotorE = new VariableInputSwitch(SPEED_MOTORe_PIN, SWITCH_MOTORe_DIRECTION1, SWITCH_MOTORe_DIRECTION2);
  Input* servoPosition = new VariableInput(SERVO_POSITION_PIN);

  // Define remote controls
  RemoteControl* remoteControl = NULL;
  int appPin = digitalRead(SWITCH_MODESELECTION_HANDY_PIN);
  if (appPin != HIGH) {
#ifdef LOG
    GetLog()->println("FlySky");
#endif
    remoteControl = new FlySky(scHard2);
  } else {
#ifdef LOG
    GetLog()->println("App");
#endif
    remoteControl = new AppInventor(scHard3);
  }

//** Define logic with relations and conditions

//* Motor A:
#ifdef LOG
  GetLog()->println("MotorA");
#endif

  // Input is in relation to the mode switch:
  Input* inputMotorA = new DependentInput(
    // Switch define the index of input to use
    modeSelectionSwitch,
    // Mode selection switch Pos0/PosMid: Manual Mode with switch: True when greather than Pos1, is when Pos2
    speedMotorA,
    // Mode selection switch Pos1: FlySky FS-I6X remote control
    remoteControl->getControl(rcJoystick1X));
  // Define logic and link motor conditionless to the DepentInput
  Relation* relationMotorA = new Relation1to1(NULL, motorA, inputMotorA);

//* Motor B:
#ifdef LOG
  GetLog()->println("MotorB");
#endif

  Input* inputMotorB = new DependentInput(
    modeSelectionSwitch,
    speedMotorB,
    remoteControl->getControl(rcJoystick1Y));

  Relation* relationMotorB = new Relation1to1(NULL, motorB, inputMotorB);

  //* Motor C:
#ifdef LOG
  GetLog()->println("MotorC");
#endif

  Input* inputMotorC = new DependentInput(
    modeSelectionSwitch,
    speedMotorC,
    remoteControl->getControl(rcJoystick2Y));

  Relation* relationMotorC = new Relation1to1(NULL, motorC, inputMotorC);

  //* Motor D:
#ifdef LOG
  GetLog()->println("MotorD");
#endif

  Input* inputMotorD = new DependentInput(
    modeSelectionSwitch,
    speedMotorD,
    remoteControl->getControl(rcJoystick2X));

  Relation* relationMotorD = new Relation1to1(NULL, motorD, inputMotorD);

  //* Motor E:
#ifdef LOG
  GetLog()->println("MotorE");
#endif
  Input* remoteControlMotorSpeedE = new RemoteVariableInputSwitch(remoteControl, rcVrB);
  Input* inputMotorE = new DependentInput(
    modeSelectionSwitch,
    speedMotorE,
    remoteControlMotorSpeedE);
  Relation* relationMotorE = new Relation1to1(NULL, motorE, inputMotorE);
  
   //* Servo:    
   GetLog()->println("Servo"); 
   // The remote control has only 8 joystick axis. Servo position use a rotation knob 
   Input* servoInput = new DependentInput(modeSelectionSwitch,
                                          servoPosition, 
                                          remoteControl->getControl(rcVrA));
   Relation* relationServo = new Relation1to1( NULL, servo, servoInput );

  delay(50);
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
