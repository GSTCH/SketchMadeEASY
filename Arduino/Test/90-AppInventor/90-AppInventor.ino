//*****************************************************************
//* Test HandyApp RemoteControl, developed with MIT AppInventor  
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
#define SOFTSERIAL_RXPIN 12
#define SOFTSERIAL_TXPIN 13

void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("AppInventor RemoteControl Test");
#endif

  //AppInventor* appInventor = new AppInventor(scHard);
  RemoteJoystickAxis* xAxis = new RemoteJoystickAxis(-200, 124, false);
  RemoteJoystickAxis* yAxis = new RemoteJoystickAxis(-119, 145, false);
  RemoteInput* channelRemoteInputs[2]{ xAxis, yAxis };

  //  AppInventor* app = new AppInventor(channelRemoteInputs, SOFTSERIAL_RXPIN, SOFTSERIAL_TXPIN);
  AppInventor* app = new AppInventor(channelRemoteInputs, scHard3);
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
