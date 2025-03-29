//*****************************************************************
//* Test for a variable input/swtch combination (=joystick axis)
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
// Parameter joystick
#define VARIABLE_INPUT_PIN A0
#define SWITCH_POS1 40
#define SWITCH_POS2 42

void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("VariableInputSwitch Test");
#endif
  // Create input
  VariableInputSwitch* dummyJoystickAxis = new VariableInputSwitch(VARIABLE_INPUT_PIN, SWITCH_POS1, SWITCH_POS2 );
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
