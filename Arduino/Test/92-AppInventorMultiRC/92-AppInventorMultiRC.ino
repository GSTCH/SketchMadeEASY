//*****************************************************************
//* Test HandyApp RemoteControl, developed with MIT AppInventor  
//*
//* This library is able to manage multiple different remote control 
//* at once. The RC to use is selectable by a switch. Because of 
//* interrupt conflict, the RC has only an active communication when
//* it's used. 
//* This test is to check the dynamic enable/disable of the RC.
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

//***************************************************************************************************************
// Parameter MainSwitch
#define SWITCH_POS1 39
#define SWITCHMODE smPullUpExternal

void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("AppInventor MultiRemoteControl Test");
#endif

  Switch2Position* mainSwitch = new Switch2Position(SWITCH_POS1, SWITCHMODE);
  CompareCondition* flySkyEnabledCondition = new CompareCondition(mainSwitch, OpEQ, Switch2Position::On );

  AppInventor* app = new AppInventor(scHard3, flySkyEnabledCondition);
  app->getControl(rcJoystick1X);
  app->getControl(rcJoystick1Y);
  app->getControl(rcJoystick2X);
  app->getControl(rcJoystick2Y);
  app->getControl(rcVrA);
  app->getControl(rcVrB);
  app->getControl(rcSwA);
  app->getControl(rcSwB);
  app->getControl(rcSwC);
  app->getControl(rcSwD);  
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
