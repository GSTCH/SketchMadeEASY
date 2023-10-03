//*****************************************************************
//* Example 16-EncoderMotor and LED controlled by FlySky FS-i6X-RemoteControl
//*
//* Hardware:
//* - Motorshield to control motor
//* - DC motor
//* - FlySky FS-i6X RemoteControl
//* - FlySky FS-iA6B Receiver (iBus)
//* - LED and 220ohm resistor
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
// Parameter MotorShield L9110
#define MOTOR_PINA1 44
#define MOTOR_PINB1 46
#define MOTOR_PINA2 11
#define MOTOR_PINB2 12
// Parameter Rotary Encoder
#define ENCA 3 // (use a interrupt when RISING, read doc to attachInterupt() to get usable pins)
#define ENCB 4
// Motor N20, n=100m 6V
#define MOTOR_RPM_MAX 60
#define PPR 7
#define GEAR_RATIO 150
// Parameter of LED
#define LED_PIN 6
#define ONBOARD_LED_PIN 13

void setup()
{
   //((*** Initialize: Configure your sketch here....
  //** Define motor at X-Axis of Joystick
  //* Create actuator: 
  // Encoder gear motor 
  EncoderMotorL9110* encoderMotor = new EncoderMotorL9110(MOTOR_PINA2, MOTOR_PINB2, ENCA, ENCB, PPR, GEAR_RATIO, 0);

  //* Create input. 
  // Input is at RemoteControl FlySky  
  FlySky* flySky = new FlySky(scHard2);

  //* Define logic with condition and relation
  Relation1to1* relationMotor = new Relation1to1(NULL, encoderMotor, flySky->getControl(rcJoystick1X));


  //** Define switch 
  //* Create actuator:
  // On board LED controlled by a switch at RC
  DigitalOutput* led = new DigitalOutput(LED_PIN);

  //* Define logic with condition and relation
  // Switch is on, brightness with a Poti on the RC
  CompareCondition* conditionSwitchOn = new CompareCondition(flySky->getControl(rcSwA), OpEQ, RemoteValue::Pos1);
  Relation1to1* switchOnRelation = new Relation1to1(conditionSwitchOn, led, flySky->getControl(rcVrA));

  // Switch is off
  CompareCondition* conditionSwitchOff = new CompareCondition(flySky->getControl(rcSwA), OpEQ, RemoteValue::Pos0);
  Relation1to1* switchOffRelation = new Relation1to1(conditionSwitchOff, led, FixValue::Off());
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