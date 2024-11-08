//*****************************************************************
//* Test FlySky FS-i6X-RemoteControl (with setting to 14 channel) 
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

#include "ui.h"
#define LOG 
#include <Easy.h>

//*****************************************************************
#define LED_PIN 32

RemoteValue Switch(FIXVALUE_LOW, FIXVALUE_HIGH);

void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Display Test");
#endif

  // Prepare
  Display* display = new Display(ttILI9341_24in);

  DigitalOutput* led = new DigitalOutput(LED_PIN);

 // Configure Logic 
  CompareCondition* conditionSwitchOff = new CompareCondition(&Switch, OpEQ, FIXVALUE_HIGH);
  Relation1to1* switchOffRelation = new Relation1to1(conditionSwitchOff, led, FixValue::High());

  CompareCondition* conditionSwitchOn = new CompareCondition(&Switch, OpEQ, FIXVALUE_LOW);
  Relation1to1* switchOnRelation = new Relation1to1(conditionSwitchOn, led, FixValue::Low());
//... ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();

  // Call the init method of the SquarelLine Studio 
  ui_init();
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

//*****************************************************************
// ui_events.c
//*****************************************************************
void ButtonEin_Clicked(lv_event_t * e)
{
	// Your code here
  Switch.SetValue(FIXVALUE_HIGH);
}

void ButtonAus_Clicked(lv_event_t * e)
{
	// Your code here
  Switch.SetValue(FIXVALUE_LOW);
}
