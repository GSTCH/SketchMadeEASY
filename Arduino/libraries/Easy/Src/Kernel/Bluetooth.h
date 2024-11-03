//*****************************************************************
//* Class Bluetooth - Header
//*
//* Implement bluetooth serial communication.
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

#ifndef EASY_BLUETOOTH_H
#define EASY_BLUETOOTH_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"

// Libraries
#include <HardwareSerial.h>
#ifndef ARDUINO_ARCH_ESP32
#include <SoftwareSerial.h>
#endif

// Internal consts and types
#define EASY_BLUETOOTH_INPUTBUFFER_SIZE 150

class Bluetooth {
  //*** PRIVATE = interna, gegen aussen verborgen.
private:
  enum ESerialMode { smNone,
                     smSoft,
                     smHard,
                     smHard1,
                     smHard2,
                     smHard3 };
#ifndef ARDUINO_ARCH_ESP32
  SoftwareSerial* _hc06;
#endif  
  ESerialMode _serialMode = smNone;
#ifndef ARDUINO_ARCH_RENESAS  
  bool _connected = false;
  bool _connectionChanged = false;
#endif
  bool _dataReceived = false;
  char _inData[EASY_BLUETOOTH_INPUTBUFFER_SIZE + 1];

  inline void LoopHardSerial();
  inline bool SendMessageHardwareSerial(const char* aMessage);
  inline void InitHardSerial();

  #ifndef ARDUINO_ARCH_ESP32    
  inline void LoopSoftSerial();
  inline bool SendMessageSoftwareSerial(const char* aMessage);
  inline void InitSoftSerial(int aRxPin, int aTxPin);
  #endif

  inline HardwareSerial* GetHardwareSerial();
public:
#ifndef ARDUINO_ARCH_ESP32    
  Bluetooth(int aRxPin, int aTxPin);
#endif  
  Bluetooth(EHardwareSerialMode aHardwareSerialMode);  
  void Setup();  
  void Loop();
  void Enable();
  void Disable();
  
  bool SendMessage(const char* aMessage);

  //*************************************
  bool DataReceived() {
    return _dataReceived;
  }

  //*************************************
  char* Data() {
    _dataReceived=false;
    return _inData;
  } 
};
#endif