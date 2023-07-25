//*****************************************************************
//* Test FlySky FS-i6X-RemoteControl (with setting to 14 channel) 
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

//*****************************************************************
// Parameter MainSwitch
#define SWITCH_POS1 39
#define SWITCHMODE smPullUpExternal

//*****************************************************************
void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("FlySky MultiRemoteControl Test");
#endif

  Switch2Position* mainSwitch = new Switch2Position(SWITCH_POS1, SWITCHMODE);

  CompareCondition* flySkyEnabledCondition = new CompareCondition(mainSwitch, OpEQ, Switch2Position::On );
  FlySky* flySky = new FlySky(scHard2, flySkyEnabledCondition);

  // Control has been created when get it --> get all controls
  flySky->getControl(rcJoystick1X);
  flySky->getControl(rcJoystick1Y);
  flySky->getControl(rcJoystick2X);
  flySky->getControl(rcJoystick2Y);
  flySky->getControl(rcVrA);
  flySky->getControl(rcVrB);
  flySky->getControl(rcSwA);
  flySky->getControl(rcSwB);
  flySky->getControl(rcSwC);
  flySky->getControl(rcSwD);
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
