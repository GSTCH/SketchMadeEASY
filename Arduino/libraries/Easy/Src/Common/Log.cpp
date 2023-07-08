//*****************************************************************
//* Class Log - Implementation
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

// Libraries
#include <Arduino.h>

// Projekt
#include "Log.h"

// Initialisierung des Static muss per CPP erfolgen.
bool Log::_enabled = false;
int Log::_baudrate = 0;
char Log::_buffer[EASY_LOG_BUFFER_LEN];

//*************************************
int Log::printf(const char* format, ...) {
  if (_enabled) {
    // Log text eats up memory and should therefore be as short as possible.
    // The class therefore supports texts with a maximum length of EASY_LOG_BUFFER_LEN characters.
    // If these are to be longer, the buffer size must be adjusted.

    va_list argptr;
    va_start(argptr, format);
    vsnprintf(_buffer, EASY_LOG_BUFFER_LEN-1, format, argptr);
    va_end(argptr);
    Serial.println(_buffer);
  }
}

//*************************************
void Log::println(const char* text) {
  if (_enabled) {
    Serial.println(text);
  }
}

//*************************************
void Log::enable(int baurate) {
  if (!_enabled) {	  
    _enabled = true;
    Serial.begin(baurate);	
	_baudrate = baurate;
  } else if (_baudrate != baurate) {
	Serial.end();
	Serial.begin(baurate);	
	_baudrate = baurate;
  }
}

//*************************************
void Log::disable() {
  if (_enabled) {
    _enabled = false;
    Serial.end();
	_baudrate = 0;
  }
}

//*************************************
void Log::flush() {
  if (_enabled) {
    Serial.flush();
  }
}