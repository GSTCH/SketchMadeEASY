//*****************************************************************
//* Example 15-RemoteControl of a motor with an App
//*
//* Hardware:
//* - Motorshield to control motor
//* - DC motor
//* - Bluetooth Shield HC-05 or HC-06 
//* - Handy with installed "Sketch made easy for Arduino"-RemoteControl App
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
#define MOTOR_SPEEDPIN 11
#define MOTOR_DIRECTIONPIN 12
// Parameter Motor L9110
#define MOTOR_PINA1 11
#define MOTOR_PINB1 12
#define MOTOR_PINA2 44
#define MOTOR_PINB2 46
// Parameter  I2C Motor
#define MOTOR_NUMBER 1
// Parameter for Bluetooth 
#define SOFTSERIAL_RXPIN 12
#define SOFTSERIAL_TXPIN 13

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Create actuator:
  // Different motor shields are supported, some are comment. Change comment and chose your motor shield.
  MotorL9110* motor = new MotorL9110(MOTOR_PINA1, MOTOR_PINB1);
  //MotorL9110* motor = new MotorL9110(MOTOR_PINA2, MOTOR_PINB2);
  //MotorL298* motor = new MotorL298(MOTOR_DIRECTIONPIN, MOTOR_SPEEDPIN);
  //MotorI2C* motor = new MotorI2C(MOTOR_NUMBER);

  //** Define Input
  // RemoteControl, connected with bluetooth.
  AppInventor* app = new AppInventor(scHard3);
  //AppInventor* app = new AppInventor(channelRemoteInputs, SOFTSERIAL_RXPIN, SOFTSERIAL_TXPIN);


  //** Define logic with condition and relation
  // No condition (NULL) because the relation is always active. 
  // With GetControl the AppInventor class creates the input control and returns its pointer. 
  Relation1to1* relationFlySkyToMotor = new Relation1to1(NULL, motor, app->getControl(rcJoystick1Y));
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