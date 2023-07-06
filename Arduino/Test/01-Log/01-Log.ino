//*****************************************************************
//* Test class for Log. This is a useful class for other sketch not
//* using "Sketch made Easy for Arduino".
//* 
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

#include <Easy.h>
#include <Arduino.h>

int i = 0;

//*****************************************************************
#define LOG_BAURATE 9600
void setup() {
  // put your setup code here, to run once:

  // At first time you can choose the baud rate (Default/no parameter is 57600).
  // Set the baud rate into the serial monitor of Arduino IDE
  GetLog(LOG_BAURATE)->printf("Text without paramter");
  GetLog()->printf("Test with parameter Int=%d, String=%s", i++, "Setup");
}

//*****************************************************************
void loop() {
  delay(100);
  // put your main code here, to run repeatedly:
  GetLog()->printf("Test with parameter Int=%d, String=%s", i++, "Loop");

  if (i == 100) {
    GetLog()->enable(false);
  }
  if (i == 200) {
    GetLog()->enable(true, LOG_BAURATE);
  }
}
