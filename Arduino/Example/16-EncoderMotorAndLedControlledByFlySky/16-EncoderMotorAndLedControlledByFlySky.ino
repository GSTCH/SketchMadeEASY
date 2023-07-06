//*****************************************************************
//* Example 14-16-EncoderMotor and LED  controlled with a FlySky FS-i6X-RemoteControl
//*
//* Hardware:
//* - Motorshield to control motor
//* - DC motor
//* - FlySky FS-i6X RemoteControl
//* - FlySky FS-iA6B Receiver (iBus)
//* - LED and 220ohm resistor
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
// Parameter motor shield
#define MOTOR_NR 2
// Parameter Rotary Encoder
#define ENCA 3
#define ENCB 4
// Parameter motor 
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
  EncoderMotorI2C* encoderMotor = new EncoderMotorI2C(MOTOR_NR, ENCA, ENCB, PPR, GEAR_RATIO, MOTOR_RPM_MAX);

  //* Create input. 
  // Input is at RemoteControl FlySky  
  FlySky* flySky = new FlySky(scHard1);

  //* Define logic with condition and relation
  Relation1to1* relationMotor = new Relation1to1(NULL, encoderMotor, flySky->getControl(rcJoystick1X));


  //** Define switch 
  //* Create actuator:
  // On board LED controlled by a switch at RC
  DigitalOutput* led = new DigitalOutput(LED_PIN);

  //* Define logic with condition and relation
  // Switch is on, brightness with a Poti on the RC
  CompareCondition* conditionSwitchOn = new CompareCondition(flySky->getControl(rcSwA), OpEQ, RemoteValue::Pos1);
  Relation1to1* switchOnRelation = new Relation1to1(conditionSwitchOn, led, flySky->getControl(rcVRA));

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