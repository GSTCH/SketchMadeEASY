//*****************************************************************
//* Class Log - Header
//*
//* Tool class to output logs on the "Serial Monitor". 
//*
//* Example:
//*   Write text only:
//*       GetLog()->printf("speed changes");
//*   Write text with parameter:
//*       GetLog()->printf("Speed changes [%d --> %d]", oldSpeed, newSpeed );
//*
//* The class can be affected to prevent a log. For example, the Bluetooth 
//* class of Easy deactivate the log, if its communicated is via HardwareSerial.
//*
//* Logs? The less the better because they need program memory. Log is for test only and has to be short.
//* When all is okay, remove the Log. For this exists the define LOG. All log have to be enclosed
//* with it:
//*
//*     #ifdef LOG_SETUP
//*       GetLog()->printf("Log during initialize");
//*     #endif
//*
//*     #ifdef LOG_LOOP
//*       GetLog()->printf("Log during loop");
//*     #endif
//*
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
//
//* (C) written in 2023 by Hans Rothenbuehler. All right reserved.
//*
//* https://github.com/GSTCH/Easy
//*
//* GNU GENERAL PUBLIC LICENSE, Version 2:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*****************************************************************
#ifndef EasyLog_h
#define EasyLog_h

#include <stdio.h>

#ifndef EASY_LOG_BUFFER_LEN
#define EASY_LOG_BUFFER_LEN 150
#endif

// Baudrates: 9600,19200,31250,38400,57600,74880,115200
#ifndef EASY_LOG_BAUDRATE
  #ifdef ARDUINO_ARCH_ESP32
    #define EASY_LOG_BAUDRATE 115200
  #else 
    #define EASY_LOG_BAUDRATE 31250
  #endif
#endif

//**********************
//*  Class Log - Header definiert die Klasse
//**********************
class Log {
  //*** PRIVATE
private:
  static bool _enabled;
  static char _buffer[EASY_LOG_BUFFER_LEN];
  static int _baudrate;

  //*** PUBLIC
public:
  Log() {}

  //************
  //* Writes a '\0'-terminierted string into the Log
  //*
  //* Example:
  //*   GetLog()->printf("Speed changes");
  //************
  void println(const char* text);

  //************
  //* Writes a string with parameters. The maximum size otf the text is EASY_LOG_BUFFER_LEN characters.
  //*
  //* Exemple:
  //*   GetLog()->printf("Speed changes from %d to %d", oldSpeed, newSpeed );
  //*
  //* Format is accoring to funktion "sprintf" in C. Doc look at web eg pages like
  //* https://www.kriwanek.de/index.php/de/arduino/sprachreferenz/393-sprintf-ausgabeformatierung
  //* https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
  //* Note that the Arduino implementaton does not supports %f.
  //************
  void printf(const char* format, ...);

  //************
  //* Activate
  //* Can be used, to prevent logging when HardwareSerial is in used by the sketch.
  //* Baudrates: 9600,19200,31250,38400,57600,74880,115200
  //************
  void enable(int baurate = EASY_LOG_BAUDRATE);
  
  //************
  //* Activate/deactive Log
  //* Can be used, to prevent logging when HardwareSerial is in used by the sketch.
  //* Baudrates: 9600,19200,38400,57600,74880,115200
  //************
  void disable();

  //************
  //* Query whether the log is activated
  //************
  inline bool enabled() {
    return _enabled;
  }
  
  //************
  //* Send all bytes buffer and wait on incomming
  //************
  void flush();  
};

//************
//* Function GetLog()
//**********************
//* Use log only via this method.
//* Implements a simple singleton pattern.
//************
static Log* GetLog(int baurate = EASY_LOG_BAUDRATE) {
  static Log* log;

  if (log == NULL) {
    log = new Log();
	  log->enable(baurate);
  }
  return log;
}

#endif
