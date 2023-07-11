//*****************************************************************
// Test FlySky FS-i6X-RemoteControl (with setting to 14 channel) 
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
void setup()
{
    //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("FlySky RemoteControl Test");
#endif

  FlySky* flySky = new FlySky(scHard2);

  // Control has been creted when get it --> get all controls
  flySky->getControl(rcJoystick1X);
  flySky->getControl(rcJoystick1Y);
  flySky->getControl(rcJoystick2X);
  flySky->getControl(rcJoystick2Y);
  flySky->getControl(rcVRA);
  flySky->getControl(rcVRB);
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
