//*****************************************************************
// Test for a toggle switch
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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
// Parameter of limit switches
#define DIRECTION_PIN1 43  
#define DIRECTION_PIN2 41  
#define SWITCHMODE smPullUpExternal

void setup()
{
//((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("ToggleSwitch Test");
#endif

  // Toggle the value between two values, change controlled by limit switches
  ToggleSwitch* toggleSwitch = new ToggleSwitch(DIRECTION_PIN1, DIRECTION_PIN2, SWITCHMODE);
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