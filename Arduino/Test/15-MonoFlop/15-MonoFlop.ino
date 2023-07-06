//*****************************************************************
//* Test for a mono flops
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
// Parameter switch
#define MONOFLOP_PIN 7
#define MONOFLOP_HIGH_DELAY_MS 2000
#define MONOFLOP_HIGH_LOW_MS 500
#define MONOFLOP_STARTIMPULSE false

void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("MonoFlop Test");
#endif

  // Create input monoflop.
  // MonoFlop has a defined duration of the signal. The duration of high and low can be configured when create.
  // Values: 0=Low, 1=LowTimerRuns, 2=LowTimerEnd, 3=High, 4=High timer runs, 5=High timer end.
 MonoFlop* monoflop = new MonoFlop(MONOFLOP_PIN, MONOFLOP_HIGH_DELAY_MS, MONOFLOP_HIGH_LOW_MS, MONOFLOP_STARTIMPULSE);
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
