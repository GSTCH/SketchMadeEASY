//*****************************************************************
//* Model01 - Stokys S224 / Option b). Tower crane with App
//*
//* Stokys tower crane S224:
//* Winch by 360° servo and tower rotation by motor.
//* The movement is controlled by a handy App (Arduino or iOS),
//* The ArduinoEasyRemoteControl App is available at http://ai2.appinventor.mit.edu/#4747037693575168
//* Parts to build the model are available at www.stokys.ch
//*
//* Video of the model: https://www.youtube.com/watch?v=jrZIEZWW-Eo
//*
//* Hardware:
//* - DC motor (Speed at PWM-PIN 10, Direction Pin=12)
//* - L298 shield to control motor
//* - Servo360 at pin 9
//* - HC06 Bluetooth shield
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

//*****************************************************************
// Parameter Motor(shield)
#define MOTOR_SPEEDPIN 10
#define MOTOR_DIRECTIONPIN 12
// Parameter Servo360
#define SERVO360_PIN 9
// Parameter HC-06 BlueTooth shield (with UNO soft serial required)
#define SOFTSERIAL_RXPIN 5
#define SOFTSERIAL_TXPIN 6

void setup() {
  //((*** Initialize: Configure your sketch here....
  //AppInventor* appInventor = new AppInventor(scHard);
  AppInventor* appInventor = new AppInventor(SOFTSERIAL_RXPIN, SOFTSERIAL_TXPIN);

  MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  Relation1to1* relationMotor = new Relation1to1(NULL, motor, appInventor->getControl(rcJoystick1X));

  MotorServo360T2* servo360 = new MotorServo360T2(SERVO360_PIN);
  Relation1to1* relationServo = new Relation1to1(NULL, servo360, appInventor->getControl(rcJoystick1Y));
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
