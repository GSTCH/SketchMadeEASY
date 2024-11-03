//*****************************************************************
//* Class Bluetooth - Implementation
//*
//* Implement CRemoteControlCommunication with Bluetooth
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

// Libraries
#include <Arduino.h>
#include <Math.h>
// Projekt
#include "Bluetooth.h"
#include "..\Common\Log.h"

//*************************************
#ifndef ARDUINO_ARCH_ESP32
Bluetooth::Bluetooth(int aRxPin, int aTxPin) {
  _serialMode = smSoft;
  InitSoftSerial(aRxPin, aTxPin);
}
#endif

//*************************************
Bluetooth::Bluetooth(EHardwareSerialMode aHardwareSerialMode) {
  switch (aHardwareSerialMode) {
    case scHard:
      _serialMode = smHard;
      break;
#if defined( __AVR_ATmega2560__) ||  defined(ARDUINO_ARCH_ESP32)      
    case scHard1:
      _serialMode = smHard1;
      break;
    case scHard2:
      _serialMode = smHard2;
      break;
#endif      
#if defined( __AVR_ATmega2560__)            
    case scHard3:
      _serialMode = smHard3;
      break;
#endif      
  }
  InitHardSerial();
}

//*************************************
void Bluetooth::Setup() {
  _inData[0] = '\0';
}

//*************************************
void Bluetooth::Loop() {
  switch (_serialMode) {
#ifndef ARDUINO_ARCH_ESP32        
    case smSoft:
      LoopSoftSerial();
      break;
#endif      
    case smHard:    
    case smHard1:
    case smHard2:
    case smHard3:
      LoopHardSerial();
      break;
    case smNone:
      // Please init!
      break;
  }

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("BT:L Co=%d CC=%d DR=%d", _connected, _connectionChanged, _dataReceived);
#endif
}

//*************************************
void Bluetooth::LoopHardSerial() {
  int amountOfBytesToReceive = GetHardwareSerial()->available();

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("BT:LHs C=%d CC=%d DR=%d, St=%d, DA=%d", _connected, _connectionChanged, _dataReceived, *GetHardwareSerial(), GetHardwareSerial()->available());
#endif

#if !defined(ARDUINO_ARCH_RENESAS)      
  if ((*GetHardwareSerial()) && !_connected) {
#ifdef LOG_LOOP
    GetLog()->println("BT:LSs active");
#endif
    _connected = true;
    _connectionChanged = true;
  }
  else if (!(*GetHardwareSerial()) && _connected) {
#ifdef LOG_LOOP
    GetLog()->println("BT:LSs disabled");
#endif
    _connected = false;
    _connectionChanged = true;
  }
#endif  

  if (amountOfBytesToReceive > 0) {
    // Command always ends with a NewsLine.
    byte size = GetHardwareSerial()->readBytesUntil('\n', _inData, EASY_BLUETOOTH_INPUTBUFFER_SIZE);

    if (size > 0) {
      // In order to get a C-String a termination has to be added.
      _inData[size] = '\0';
#ifdef LOG_LOOP
      GetLog()->printf("BT:LHs Rcv %d [%s]", size, _inData);
#endif
    }
    else {
      _inData[0] = '\0';
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("BT:LHs Rcv 0");
#endif
    }

    _dataReceived = size > 0;
  }
}

//*************************************
#if ! defined(ARDUINO_ARCH_ESP32) 
void Bluetooth::LoopSoftSerial() {
  int amountOfBytesToReceive = _hc06->available();

#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("BT:LSs DR=%d, DA=%d", _dataReceived, amountOfBytesRoReceive);
#endif

#if !defined(ARDUINO_ARCH_RENESAS)
  if ((*_hc06) && !_connected) {
#ifdef LOG_LOOP
    GetLog()->println("BT:LSs active");
#endif
    _connected = true;
    _connectionChanged = true;
  }
  else if (!*_hc06 && _connected) {
#ifdef LOG_LOOP
    GetLog()->println("BT:LSs disabled");
#endif
    _connected = false;
    _connectionChanged = true;
  }
#endif

  if (amountOfBytesToReceive > 0) {
    // Buffer leeren.
    _inData[0] = '\0';

    // Command always ends with a NewsLine.
    byte size = _hc06->readBytesUntil('\n', _inData, EASY_BLUETOOTH_INPUTBUFFER_SIZE);

    if (size > 0) {
      // In order to get a C-String a termination has to be added.
      _inData[size] = 0;
#ifdef LOG_LOOP
      GetLog()->printf("BT:LSs Rcv %d [%s]", size, _inData);
#endif
    }
    else {
      _inData[0] = 0;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("BT:LSs Rcv 0");
#endif
    }

    _dataReceived = size > 0;
  }
}
#endif

//*************************************
bool Bluetooth::SendMessage(const char* aMessage) {
  switch (_serialMode) {
#ifndef ARDUINO_ARCH_ESP32    
    case smSoft:
      return SendMessageSoftwareSerial(aMessage);
#endif      
    case smHard:
    case smHard1:
    case smHard2:
    case smHard3:
      return SendMessageHardwareSerial(aMessage);
    case smNone:
      // Please init!
      break;
  }
  return false;
}

//*************************************
#ifndef ARDUINO_ARCH_ESP32    
bool Bluetooth::SendMessageSoftwareSerial(const char* aMessage) {
  return _hc06->println(aMessage) > 0;
}
#endif  

//*************************************
bool Bluetooth::SendMessageHardwareSerial(const char* aMessage) {
  return GetHardwareSerial()->println(aMessage) > 0;
}

//*************************************
void Bluetooth::InitHardSerial() {
  if (_serialMode == smHard) {
#ifdef LOG_SETUP
    GetLog()->printf("BT:IHs Sx=0, M=%d", _serialMode);
#endif

    // SerialMonitor (Log) and bluetooth have conflics at Nano and Uno. Mega has three additional hardware serial channels.
    if (GetLog()->enabled()) {
      GetLog()->disable();
    }
    return;
  }

#ifdef LOG_SETUP
  GetLog()->printf("BT:IHs Sx=%d M=%d", _serialMode - 2, _serialMode);
#endif

#ifdef __AVR_ATmega2560__
  switch (_serialMode) {
    case smHard1:
      pinMode(19, INPUT_PULLUP);  // fix Serial1
      break;
    case smHard2:
      pinMode(17, INPUT_PULLUP);  // fix Serial2
      break;
    case smHard3:
      pinMode(15, INPUT_PULLUP);  // fix Serial3
      break;
  }
#endif
}

//*************************************
#ifndef ARDUINO_ARCH_ESP32    
void Bluetooth::InitSoftSerial(int aRxPin, int aTxPin) {
  GetLog()->enable();

  pinMode(aRxPin, INPUT);
  pinMode(aTxPin, OUTPUT);
  _hc06 = new SoftwareSerial(aRxPin, aTxPin);

#ifdef LOG_SETUP
  GetLog()->printf("BT:ISs RX=%d, TX=%d", aRxPin, aTxPin);
#endif

  delay(50);
  _hc06->begin(9600);  //9600,19200,38400,5760
  while (_hc06->available() > 0)
  {
    // Emtiing buffer
    _hc06->read();
  }
}
#endif

//*************************************
inline HardwareSerial* Bluetooth::GetHardwareSerial() {
  switch (_serialMode) {
    case smHard:
#if !defined(__AVR_ATmega328P__) && !defined(ARDUINO_ARCH_ESP32)
      // Arduino Uno has only one HardSerial. Disable log to prevent conflicts.
      GetLog()->disable();
#endif  
      return &Serial;
#if defined(__AVR_ATmega2560__) || defined(ARDUINO_ARCH_ESP32)
      // Board specific condition compilation. Mega supports 4 serial. Infos look http://www.nongnu.org/avr-libc/user-manual/using_tools.html
    case smHard1:
      return &Serial1;
#endif      
#ifdef __AVR_ATmega2560__      
    case smHard2:
      return &Serial2;
    case smHard3:
      return &Serial3;
#endif      
    default:
#ifdef LOG_LOOP
      GetLog()->printf("BT:G Not supported mode");
#endif  // LOG
      return NULL;
  }
}

//*************************************
void Bluetooth::Enable()
{
  switch (_serialMode) {
#ifndef ARDUINO_ARCH_ESP32        
    case smSoft:
      _hc06->begin(9600);      
      break;
#endif      
    case smHard:
    case smHard1:
    case smHard2:
    case smHard3:
      GetHardwareSerial()->begin(9600);
    case smNone:
      // Please init!
      break;
  }
}

//*************************************
void Bluetooth::Disable()
{
  switch (_serialMode) {
#ifndef ARDUINO_ARCH_ESP32        
    case smSoft:
#ifndef ARDUINO_ARCH_RENESAS
      _hc06->end();
#endif      
      break;
#endif      
    case smHard:
    case smHard1:
    case smHard2:
    case smHard3:
      GetHardwareSerial()->end();
      break;
    case smNone:
      // Please init!
      break;
  }
}

