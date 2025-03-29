//*****************************************************************
//* Test RemoteVariableInputSwitch
//*
//* Control simulates a joystick axis. Switch SwC defines the direction
//* variable input VrA or VrB defines the speed.
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
void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("RemoteVariableInputSwitch Test");
#endif

  RemoteControl* flySky = new FlySky(scHard2);
  /*
  RemoteInput* variableSpeed = flySky->getControl(rcVrB);
  RemoteInput* directionSwitch = flySky->getControl(rcSwC);
  Input* remoteVariableInput = new RemoteVariableInputSwitch(variableSpeed, directionSwitch);
  */
  /*
  Input* remoteVariableInput = new RemoteVariableInputSwitch(flySky, rcVrB, rcSwC);
  */

  Input* remoteVariableInput = new RemoteVariableInputSwitch(flySky);
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
