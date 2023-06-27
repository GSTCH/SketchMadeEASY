//*****************************************************************
//* Test for a toggle loop button
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

#include <Easy.h>
#include <Arduino.h>
#define LOG 
#define LOG_LOOP

//*****************************************************************
// Parameter loop switch
#define LOOPSWITCH_BUTTON_PIN 7
#define LOOPSWITCH_MIN 1
#define LOOPSWITCH_MAX 5
#define LOOPSWITCH_STEPWIDTH 1

void setup()
{
//((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("LoopSwitch Test");
#endif


  // Create input loop switch
  // Each press of the button changes the value within the defined range.
  LoopSwitch* loopSwitch = new LoopSwitch(LOOPSWITCH_BUTTON_PIN, LOOPSWITCH_MIN, LOOPSWITCH_MAX, LOOPSWITCH_STEPWIDTH);
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
