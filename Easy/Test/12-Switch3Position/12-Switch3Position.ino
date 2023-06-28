//*****************************************************************
//* Test for Switch3Position
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
//*
//* Hint: Does not set debounce (works with default)
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
// Parameter of Switch1
//#define SWITCH_POS1 36
//#define SWITCH_POS2 37
//#define SWITCHMODE smPullUpExternal

// Parameter of Switch2
#define SWITCH_POS1 40
#define SWITCH_POS2 42
#define SWITCHMODE smPullDownInternal

void setup()
{
//((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Switch3Position Test");
#endif

  Switch3Position* switch3Pos = new Switch3Position(SWITCH_POS1, SWITCH_POS2, SWITCHMODE);
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

