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
#define SOFTSERIAL_RXPIN 2
#define SOFTSERIAL_TXPIN 3

void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("AppInventor RemoteControl Test");
#endif

  
  //AppInventor* app = new AppInventor(SOFTSERIAL_RXPIN, SOFTSERIAL_TXPIN);
  AppInventor* app = new AppInventor(scHard3);
  
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
