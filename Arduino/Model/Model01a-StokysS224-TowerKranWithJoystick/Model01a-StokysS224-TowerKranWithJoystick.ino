//*****************************************************************
//* Model01 - Stokys S224 / Option a). Tower crane with Joystick (Prototyp 2021)
//*
//* Stokys tower crane S224: 
//* Winch by 360° servo and tower rotation by motor. 
//* The movement is controlled by an analog XY joystick. The joystick
//* calibrates itself. Do not move during startup of Arduino!
//* Parts to build the model are available at www.stokys.ch
//*
//* Hardware:
//* - DC motor (Speed at PWM-PIN 10, Direction Pin=12)
//* - L298 shield to control motor
//* - Servo360 at pin 9
//* - analog Joystick with two 10kOhm potentiometer at Pin A1 and A2
//*
//* In the directory with the example is also a picture of the breadboard.
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


// Parameter Motor(shield)
#define MOTOR_SPEEDPIN 10
#define MOTOR_DIRECTIONPIN 12
// Parameter Servo360
#define SERVO360_PIN 9
// Parameter Joystick
#define JOYSTICK_XAXIS_PIN A2
#define JOYSTICK_YAXIS_PIN A1

//***************************************************************************************************************
void setup()
{
  //((*** Initialize: Configure your sketch here....
  // Define motor to Joystick X-Axis:
  MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  JoystickAxis* xAxis = new JoystickAxis(JOYSTICK_XAXIS_PIN, true);
  Relation1to1* relationMotor = new Relation1to1(NULL, motor, xAxis);

  // Define servo 360° to Joystick Y-Axis:
  MotorServo360T2* servo360 = new MotorServo360T2(SERVO360_PIN);
  JoystickAxis* yAxis = new JoystickAxis(JOYSTICK_YAXIS_PIN, false);
  Relation1to1* relationServo = new Relation1to1(NULL, servo360, yAxis);
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
