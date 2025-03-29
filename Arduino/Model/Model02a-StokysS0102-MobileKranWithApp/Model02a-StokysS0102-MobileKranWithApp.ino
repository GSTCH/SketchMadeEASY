//*****************************************************************
//* Model02 - Stokys S0102 - Mobile crane with App
//*
//* Stokys mobile crane 0102. 
//* Winch via a 360 ° servo. Drive and steer by two motors that turn 
//* at different speeds like a caterpillar vehicle. The movement of 
//* the vehicle depends on the X / Y position: straight ahead, local 
//* steering right, ..
//* The movement is controlled by a handy App (Arduino or iOS),
//* The ArduinoEasyRemoteControl App is available at http://ai2.appinventor.mit.edu/#4747037693575168
//* Parts to build the model are available at www.stokys.ch
//*
//* Video of the model:
//*   https://www.youtube.com/watch?v=L8hPWEczd0I
//* 
//* Hardware:
//* - L298 motor shield to control the two DC-Motor N20
//* - Servo360
//* - HC06 Bluetooth shield
//* - Buzzer
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
// Parameter Buzzer (when drive backward)
#define BUZZER_FREQUENCY 1000
#define BUZZER_ONTIME 1200
#define BUZZER_OFFTIME 800
#define BUZZER_PIN 4
// Parameter Motorshield
#define MOTOR_LEFT_MOTOR_DIRECTIONPIN 12
#define MOTOR_LEFT_SPEEDPIN 10
#define MOTOR_RIGHT_MOTOR_DIRECTIONPIN 13
#define MOTOR_RIGHT_SPEEDPIN 11
// Parameter Servo360
#define SERVO360_PIN 9
// Parameter bluetooth shield (Arduino Uno with Log) 
#define SOFTSERIAL_RXPIN 5
#define SOFTSERIAL_TXPIN 6

// Parameter Crawler Steering
#define PIVOTWIDTH 10

void setup()
{
  RemoteControl* remoteControl = new AppInventor(scHard);
  //RemteControl* remoteControl = new AppInventor(SOFTSERIAL_RXPIN, SOFTSERIAL_TXPIN);

  Actuator* motorLeft = new MotorL298(MOTOR_LEFT_MOTOR_DIRECTIONPIN, MOTOR_LEFT_SPEEDPIN);
  Actuator* motorRight = new MotorL298(MOTOR_RIGHT_MOTOR_DIRECTIONPIN, MOTOR_RIGHT_SPEEDPIN);

  Relation* steering = new CrawlerSteering(NULL, motorRight, motorLeft, remoteControl->getControl(rcJoystick1X), remoteControl->getControl(rcJoystick1Y), PIVOTWIDTH);

  Actuator* servo360 = new MotorServo360Pwm(SERVO360_PIN);
  Relation* relationServo = new Relation1to1(NULL, servo360, remoteControl->getControl(rcJoystick2Y));

  Buzzer* buzzer = new Buzzer(BUZZER_PIN, BUZZER_FREQUENCY, BUZZER_ONTIME, BUZZER_OFFTIME);
  Condition* conditionBuzzerOn = new CompareCondition(remoteControl->getControl(rcJoystick1Y), OpLT, 0);
  Relation.* relationBuzzerOn = new Relation1to1(conditionBuzzerOn, buzzer, remoteControl->getControl(rcJoystick1Y));
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
