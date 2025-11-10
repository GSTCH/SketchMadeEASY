//*****************************************************************
//* EyeControl for RModel06-Stokys-RobiTheWinner
//* Random movement of the eyes in X/Y by two servos.
//*
//* Hardware: 
//* - PWM-I2C Shield with an Arduino Uno R3. 
//* - Two (25kg) Servo 
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
//
//* (C) written in 2025 by Hans Rothenbühler. All right reserved.
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

// Switch 3-Position (PullDownInternal)
#define POSITION_1_PIN 14 // A0
#define POSITION_2_PIN 15 // A1
#define SWITCHMODE smPullDownInternal

//Joystick of manual mode
#define JOYSTICK_X_INPUT_PIN A2
#define JOYSTICK_Y_INPUT_PIN A3
// A4+A5 used by I2C

// Automatic mode
#define STEPWIDTH_HORIZONTAL_MSEC 227

// Iterator do not drive full range
#define SERVO_HORIZONTAL_ANGLE_DRIVE_MIN 45
#define SERVO_HORIZONTAL_ANGLE_DRIVE_MAX 135
#define HORIZONTAL_ANGLE_STEPWIDTH_DEGREE 1

// Parameter Servo1
#define SERVO_HORIZONTAL_NR 6
#define SERVO_HORIZONTAL_ANGLE_MIN 0
#define SERVO_HORIZONTAL_ANGLE_MAX 180

// Parameter Servo2
#define SERVO_VERTICAL_NR 7
#define SERVO_VERTICAL_ANGLE_MIN 0
#define SERVO_VERTICAL_ANGLE_MAX 180

void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Roby EyeControl");
#endif

  // Servos
  ServoI2C* servoHorizontal = new ServoI2C(SERVO_HORIZONTAL_ANGLE_MIN, SERVO_HORIZONTAL_ANGLE_MAX, SERVO_HORIZONTAL_NR);
  ServoI2C* servoVertical = new ServoI2C(SERVO_VERTICAL_ANGLE_MIN, SERVO_VERTICAL_ANGLE_MAX, SERVO_VERTICAL_NR);

  // Modes with a switch with 3 positions:
  // - MiddlePos: Centre position to adjust the excenters
  // - Pos1: Automatic eye movement
  // - Pos2: Manual mode, move eyes by joystick.
  Input* modeSwitch = new Switch3Position(POSITION_1_PIN, POSITION_2_PIN, SWITCHMODE);

  // Define movement of Servo in XY-Direction of automatic mode (Pos1)
  Condition* autoMode = new CompareCondition(modeSwitch, OpEQ, Switch3Position::Pos1 );
  Input* horizontalValue = new IteratorValue(SERVO_HORIZONTAL_ANGLE_DRIVE_MIN, SERVO_HORIZONTAL_ANGLE_DRIVE_MAX, HORIZONTAL_ANGLE_STEPWIDTH_DEGREE, STEPWIDTH_HORIZONTAL_MSEC, cmMin2Max2Min);
  horizontalValue->SetMinMaxValue(SERVO_HORIZONTAL_ANGLE_MIN, SERVO_HORIZONTAL_ANGLE_MAX);
  Relation* eyeSimulator = new EyeControl(autoMode, horizontalValue,servoHorizontal, servoVertical);

  // Define movement of Servo in XY-Direction of manual mode (Pos2)
  Condition* manualMode = new CompareCondition(modeSwitch, OpEQ, Switch3Position::Pos2 );
  Input* joystickX = new JoystickAxis(JOYSTICK_X_INPUT_PIN, false);
  Relation* relationServoManualHorizonal = new Relation1to1(manualMode, servoHorizontal, joystickX);
  Input* joystickY = new JoystickAxis(JOYSTICK_Y_INPUT_PIN, true);
  Relation* relationServoManualVertical = new Relation1to1(manualMode, servoVertical, joystickY);
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required

#ifdef LOG_LOOP_DEBUG
  GetLog()->println("Loop");
#endif

  ControlManagerFactory::GetControlManager()->Loop();

  delay(5);
}
