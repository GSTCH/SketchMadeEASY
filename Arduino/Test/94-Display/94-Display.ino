//*****************************************************************
//* Test Display ILI941 with Touch to enable/disable a LED
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
#include <lvgl.h>
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

  // Prepare screen
  lv_obj_add_state( ui_ButtonOff, LV_STATE_DISABLED );
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
void ButtonOn_Clicked(lv_event_t * e)
{
	// Switch lamp on 
  Switch.SetValue(FIXVALUE_HIGH);

  // Enable/disable buttons
  lv_obj_add_state( ui_ButtonOn, LV_STATE_DISABLED );
  lv_obj_clear_state( ui_ButtonOff, LV_STATE_DISABLED );
}

void ButtonOff_Clicked(lv_event_t * e)
{
	// Switch lamp off
  Switch.SetValue(FIXVALUE_LOW);

  // Enable/disable buttons
  lv_obj_clear_state( ui_ButtonOn, LV_STATE_DISABLED );
  lv_obj_add_state( ui_ButtonOff, LV_STATE_DISABLED );
}
