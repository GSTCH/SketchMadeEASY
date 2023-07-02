//*****************************************************************
//* Example19 - Buzzer ton in relation to distance
//*
//* Buzzer tone, frequence in relation to distance
//*
//* Hardware:
//* - Buzzer
//* - Ultrasonic Sensor HY-SRF05
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

//****************************************************************
#define ECHO_PIN 13
#define TRIGGER_PIN 12
#define MEASURE_INTERVAL_MSEC 1000
#define BUZZER_FREQUENCY_MIN 20
#define BUZZER_FREQUENCY_MAX 1000
#define BUZZER_PIN 4

void setup()
{
  //((*** Initialize: Configure your sketch here....
  //** Define Input
  UltrasonicRangefinder* distanceSensor = new UltrasonicRangefinder(ECHO_PIN, TRIGGER_PIN, MEASURE_INTERVAL_MSEC); 
  
  //** Define Actuators:
  Buzzer* buzzer = new Buzzer(BUZZER_PIN, BUZZER_FREQUENCY_MIN, BUZZER_FREQUENCY_MAX);

  //** Define logic with condition and relation
  Relation1to1* relationBuzzerOn = new Relation1to1(NULL, buzzer, distanceSensor);
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
