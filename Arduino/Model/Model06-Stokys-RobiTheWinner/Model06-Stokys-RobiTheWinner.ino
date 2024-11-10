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
#define MIN_BALLS 5
#define MAX_BALLS 45
#define DEFAULT_BALLS 21
RemoteValue TotalAmountOfBalls(MIN_BALLS, MAX_BALLS);

void setup()
{
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Display Test");
#endif

  // Prepare
  Display* display = new Display(ttILI9341_24in);
  
  // Initialize
  TotalAmountOfBalls.SetValue(DEFAULT_BALLS);

 // Configure Logic 
  


//... ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();

  // Call the init method of the SquarelLine Studio 
  ui_init();

  // Prepare screen
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
void ButtonSettingsOkayClicked(lv_event_t * e)
{
  int32_t value = lv_slider_get_value(ui_SliderBallAmount);
  TotalAmountOfBalls.SetValue(value);
}

void ButtonStartGameClicked(lv_event_t * e)
{
	// Your code here
}

void ButtonTakeOneClicked(lv_event_t * e)
{
	// Your code here
}

void ButtonTakeTwoClicked(lv_event_t * e)
{
	// Your code here
}

void ButtonTakeThreeClicked(lv_event_t * e)
{
	// Your code here
}

void ButtonGameFinshedClick(lv_event_t * e)
{
	// Your code here
}

void ButtonOpenSettingClicked(lv_event_t * e)
{
	lv_slider_set_value(ui_SliderBallAmount, TotalAmountOfBalls.Value(), LV_ANIM_OFF);
  lv_slider_set_range(ui_SliderBallAmount, MIN_BALLS, MAX_BALLS);
}

