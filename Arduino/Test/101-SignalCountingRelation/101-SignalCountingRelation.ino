//*****************************************************************
//* Test SignalCountingRelation
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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
// Parameter MainSwitch
#define SWITCH_PIN 39
#define AMOUNT_OF_SIGNAL_BEFORE_STOP 3
#define LIMIT_SWITCH 36
#define SWITCHMODE smPullUpExternal
#define MOTOR_NUMBER 2
#define WAIT_UNTIL_ACCEPT_NEXT_INPUT_MSEC 1000

//*****************************************************************
void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("SignalCountingRelation Test");
#endif
  Input* amountOfSignal = new FixValue(AMOUNT_OF_SIGNAL_BEFORE_STOP);
  Actuator* motor = new MotorI2C(MOTOR_NUMBER);
  Input* _actionParameter = NULL;

  Input* countedInput = new Switch2Position(LIMIT_SWITCH);
  Condition* countCondition = new CompareCondition( countedInput, OpEQ, Switch2Position::On);

  Input* startSwitch = new Switch2Position(SWITCH_PIN);
  Condition* startCondition = new CompareCondition(startSwitch, OpEQ, Switch2Position::On);

  Relation* signalCountingRelation = new SignalCountingRelation(startCondition,countCondition, amountOfSignal, motor, WAIT_UNTIL_ACCEPT_NEXT_INPUT_MSEC);
  // ***))

//((*** Initialize: Configure your sketch here....

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();

#ifdef LOG
  GetLog()->printf("SignalCountingRelation Test Ini Finished");
#endif
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
