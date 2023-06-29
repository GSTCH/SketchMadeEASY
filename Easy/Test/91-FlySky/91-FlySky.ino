//*****************************************************************
// Test FlySky FS-i6X-RemoteControl (with setting to 10 channel) 
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

  FlySky* flySky = new FlySky(scHard1);

  // Control has been creted when get it --> get all controls
  flySky->GetControl(fcJoystick1X);
  flySky->GetControl(fcJoystick1Y);
  flySky->GetControl(fcJoystick2X);
  flySky->GetControl(fcJoystick2Y);
  flySky->GetControl(fcVRA);
  flySky->GetControl(fcVRB);
  flySky->GetControl(fcSwA);
  flySky->GetControl(fcSwB);
  flySky->GetControl(fcSwC);
  flySky->GetControl(fcSwD);
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
