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
Bluetooth::Bluetooth(int aRxPin, int aTxPin) {
  _serialMode = smSoft;
  InitSoftSerial(aRxPin, aTxPin);
}

//*************************************
Bluetooth::Bluetooth(EHardwareSerialMode aHardwareSerialMode) {
  switch (aHardwareSerialMode) {
    case scHard:
      _serialMode = smHard;
      break;
    case scHard1:
      _serialMode = smHard1;
      break;
    case scHard2:
      _serialMode = smHard2;
      break;
    case scHard3:
      _serialMode = smHard3;
      break;
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
    case smSoft:
      LoopSoftSerial();
      break;
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
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("BT:LHs C=%d CC=%d DR=%d, St=%d, DA=%d", _connected, _connectionChanged, _dataReceived, *GetHardwareSerial(), GetHardwareSerial()->available());
#endif

  if ((*GetHardwareSerial()) && !_connected) {
    _connected = true;
    _connectionChanged = true;
  } else if (!(*GetHardwareSerial()) && _connected) {
    _connected = false;
    _connectionChanged = true;
  }

  if (GetHardwareSerial()->available() > 0) {
    // Command always ends with a NewsLine.
    byte size = GetHardwareSerial()->readBytesUntil('\n', _inData, EASY_BLUETOOTH_INPUTBUFFER_SIZE);

    if (size > 0) {
      // In order to get a C-String a termination has to be added.
      _inData[size] = '\0';
#ifdef LOG_LOOP
      GetLog()->printf("BT:LHs Rcv %d [%s]", size, _inData);
#endif
    } else {
      _inData[0] = '\0';
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("BT:LHs Rcv 0");
#endif
    }

    _dataReceived = size > 0;
  }
}

//*************************************
void Bluetooth::LoopSoftSerial() {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("BT:LSs C=%d CC=%d DR=%d, DA=%d", _connected, _connectionChanged, _dataReceived, _hc06->available());
#endif

  if ((*_hc06) && !_connected) {
#ifdef LOG_LOOP
    GetLog()->println("BT:LSs active");
#endif
    _connected = true;
    _connectionChanged = true;
  } else if (!*_hc06 && _connected) {
#ifdef LOG_LOOP
    GetLog()->println("BT:LSs disabled");
#endif
    _connected = false;
    _connectionChanged = true;
  }

  if (_hc06->available() > 0) {
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
    } else {
      _inData[0] = 0;
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("BT:LSs Rcv 0");
#endif
    }

    _dataReceived = size > 0;
  }
}

//*************************************
bool Bluetooth::SendMessage(const char* aMessage) {
  switch (_serialMode) {
    case smSoft:
      return SendMessageSoftwareSerial(aMessage);
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
bool Bluetooth::SendMessageSoftwareSerial(const char* aMessage) {
  return _hc06->println(aMessage) > 0;
}

//*************************************
bool Bluetooth::SendMessageHardwareSerial(const char* aMessage) {
  return GetHardwareSerial()->println(aMessage) > 0;
}

//*************************************
void Bluetooth::InitHardSerial() {
  if (_serialMode == smHard) {
#ifdef LOG_LOOP
    GetLog()->printf("BT:IHs Sx=0, M=%d", _serialMode);
#endif

    // SerialMonitor (Log) and bluetooth have conflics at Nano and Uno. Mega has three additional hardware serial channels.
    if (GetLog()->enabled()) {
      GetLog()->disable();
    }
    return;
  }

#ifdef LOG_LOOP
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

  GetHardwareSerial()->begin(9600);
}

//*************************************
void Bluetooth::InitSoftSerial(int aRxPin, int aTxPin) {
  GetLog()->enable(true);

  if (_serialMode != smNone) {
#ifdef LOG_LOOP
    GetLog()->printf("BT:ISs ERROR! n init");
#endif
    return;
  }

  pinMode(aRxPin, INPUT);
  pinMode(aTxPin, OUTPUT);

#ifdef LOG_LOOP
  GetLog()->printf("BT:ISs RX=%d, TX=%d", aRxPin, aTxPin);
#endif

  _hc06 = new SoftwareSerial(aRxPin, aTxPin);
  _hc06->begin(9600);  //9600,19200,38400,57600
}

//*************************************
inline HardwareSerial* Bluetooth::GetHardwareSerial() {
  switch (_serialMode) {
    case smHard:
      return &Serial;
      // Board specific condition compilation. Mega supports 4 serial. Infos look http://www.nongnu.org/avr-libc/user-manual/using_tools.html
#ifdef __AVR_ATmega2560__
    case smHard1:
      return &Serial1;
    case smHard2:
      return &Serial2;
    case smHard3:
      return &Serial3;
#endif  // __AVR_ATmega2560__
    default:
#ifdef LOG_LOOP
      GetLog()->printf("BT:G Not supported mode");
#endif  // LOG
      return NULL;
  }
}