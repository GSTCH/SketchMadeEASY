//*****************************************************************
//* Test for DigitalInput
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
#define DIGITALINPUT_PIN 39

void setup() {
	
//((*** Initialize: Configure your sketch here....
  GetLog()->printf("Setup DigitalInput Test");

  DigitalInput* digitalInput = new DigitalInput(DIGITALINPUT_PIN);
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
