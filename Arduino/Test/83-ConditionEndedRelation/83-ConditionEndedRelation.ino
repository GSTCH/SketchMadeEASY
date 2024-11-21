//*****************************************************************
//* Test for ConditionEndedRelation
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2024 by Hans Rothenbühler. All right reserved.
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
// Parameter switch
#define SWITCH1PIN 39
#define SWITCH1MODE smPullUpExternal

// Parameter of Switch2
#define SWITCH2PIN 40
#define SWITCH2MODE smPullDownInternal

#define ONBOARD_LED_PIN 13
#define LED_PIN 6

void setup() {
//((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Setup ConditionEndedRelation Test");
#endif

  Input* switchOnOff = new Switch2Position(SWITCH1PIN, SWITCH1MODE);
  Input* switchEnd = new Switch2Position(SWITCH2PIN, SWITCH2MODE);

  Actuator* led = new DigitalOutput(LED_PIN);

  Condition* activeCondition = new CompareCondition(switchOnOff, OpEQ, Switch2Position::On);
  Condition* endCondition = new CompareCondition(switchEnd, OpEQ, Switch2Position::Off);

  Relation* relation = new ConditionEndedRelation(activeCondition, endCondition, led, FixValue::On(), FixValue::Off());

  // with no end condition, it's like a 1:1 relation with an ELSE  (FalseValue). Default is TrueParam=High, FalseParam=Low. 
  //Relation* relation = new ConditionEndedRelation(activeCondition, NULL, led);
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
