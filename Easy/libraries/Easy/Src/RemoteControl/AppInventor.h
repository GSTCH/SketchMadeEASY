//*****************************************************************
//* Class AppInventor - Header
//*
//* Logic of the AppInventor-RemoteControl (HandyApp)
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

#ifndef AppInventor_h
#define AppInventor_h

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "..\Kernel\RemoteControl.h"
#include "..\Kernel\Bluetooth.h"
#include "RemoteValue.h"
#include "RemoteJoystickAxis.h"
#include <Arduino.h>

#define APPINVENTOR_JOYSTICK1_minX -200
#define APPINVENTOR_JOYSTICK1_maxX 200
#define APPINVENTOR_JOYSTICK1_minY -120
#define APPINVENTOR_JOYSTICK1_maxY 120
#define APPINVENTOR_SLIDER1_MIN -120
#define APPINVENTOR_SLIDER1_MAX 120
#define APPINVENTOR_SLIDER2_MIN -120
#define APPINVENTOR_SLIDER2_MAX 120
#define APPINVENTOR_COMMANDBUFFER_SIZE 100


class AppInventor : public RemoteControl {
private:
  Bluetooth* _bluetooth;
  char _commandBuffer[APPINVENTOR_COMMANDBUFFER_SIZE + 1];

  //*************************************
  inline int numberLen(int aNumber) {
    if (aNumber < 10) return 1;
    if (aNumber < 100) return 2;
    return 3;
  }

  //*************************************
  inline bool knownCommand(char aCommand) {
    switch (aCommand) {
      case 'A':
      case 'D':
      case 'W':
      case 'V':
        return true;
    }
    return false;
  }

  //*************************************
  inline void ParseAndUpdateTelegram() {
    if (_commandBuffer[0] == '\0') {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("AI:PT Buffer is empty");
#endif
      return;
    }

    char* command = strtok(_commandBuffer, ",");
    if (command == NULL) {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("AI:PT No command received");
#endif
      return;
    }

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("AI:PT %s Cd=%s", _commandBuffer, command);
#endif
    int cutLen = 1;
    switch (command[0]) {
      case 'W':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[2] = atoi(value);
            if (_channelRemoteInputs[2] != NULL) {
              _channelRemoteInputs[2]->SetMapValue(_channelValue[2], APPINVENTOR_SLIDER1_MIN, APPINVENTOR_SLIDER1_MAX);
            }
            cutLen = 3 + numberLen(_channelValue[2]);
          }
        }
      case 'V':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[3] = atoi(value);
            if (_channelRemoteInputs[3] != NULL) {
              _channelRemoteInputs[3]->SetMapValue(_channelValue[3], APPINVENTOR_SLIDER2_MIN, APPINVENTOR_SLIDER2_MAX);
            }
            cutLen = 3 + numberLen(_channelValue[3]);
          }
        }
        break;
      case 'D':
        {
          char* xAxis = strtok(NULL, ",");
          if (xAxis != NULL) {
            _channelValue[0] = atoi(xAxis);
            if (_channelRemoteInputs[0] != NULL) {
              _channelRemoteInputs[0]->SetMapValue(_channelValue[0], APPINVENTOR_JOYSTICK1_minX, APPINVENTOR_JOYSTICK1_maxX);
            }
            char* yAxis = strtok(NULL, ",");
            if (yAxis != NULL) {
#ifdef LOG_LOOP_DEBUG
              GetLog()->printf("AI:PT Js X=%s Y=%s", xAxis, yAxis);
#endif
              _channelValue[1] = atoi(yAxis);
              if (_channelRemoteInputs[1] != NULL) {
                _channelRemoteInputs[1]->SetMapValue(_channelValue[1], APPINVENTOR_JOYSTICK1_minY, APPINVENTOR_JOYSTICK1_maxY);
              }
              cutLen = 4 + numberLen(_channelValue[0]) + numberLen(_channelValue[1]);
            } else {
              cutLen = 3 + numberLen(_channelValue[0]);
            }
          }
        }
        break;
      case 'A':
        // No connection monitoring is currently implemented. The LED on the HC06
        // lights up every second to see whether communication is taking place.
        cutLen = 2;
        break;
      default:

#ifdef LOG_LOOP
        GetLog()->printf("AI:PT Unkown Cd recvd %02x", (uint8_t)command[0]);
#endif
        for (int idx = strlen(command); idx < APPINVENTOR_COMMANDBUFFER_SIZE; ++idx) {
          if (_commandBuffer[idx] == '\0') {
#ifdef LOG_LOOP_DEBUG
            GetLog()->printf("AI:PT Empting buffer", (uint8_t)command[0]);
#endif
            // Nothing found, clear buffer
            _commandBuffer[0] = '\0';
          }

          if (knownCommand(_commandBuffer[idx])) {
#ifdef LOG_LOOP_DEBUG
            GetLog()->printf("AI:PT Known command", (uint8_t)command[idx]);
#endif
            break;
          }

          ++cutLen;
        }
        break;
    }

    _commandBuffer[cutLen - 1] = '\0';
    strncpy(_commandBuffer, &_commandBuffer[cutLen], APPINVENTOR_COMMANDBUFFER_SIZE-cutLen);

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("AI:PT cut %d, Cmd=%d %d %d", cutLen, _commandBuffer[0], _commandBuffer[1], _commandBuffer[2]);
#endif
  }

protected:
  //*************************************
  bool DoSendMessage(const char* aMessage) {
    return _bluetooth->SendMessage(aMessage);
  }

public:
  //*************************************
  AppInventor(RemoteInput** aRemoteInputs, int aRxPin, int aTxPin)  // SoftSerial
    : RemoteControl(rcAppInventor, aRemoteInputs) {
    // Hardware serial
    _bluetooth = new Bluetooth(aRxPin, aTxPin);
  }

  //*************************************
  AppInventor(RemoteInput** aRemoteInputs, EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rcAppInventor, aRemoteInputs) {
    // Hardware serial only
    _bluetooth = new Bluetooth(aHardwareSerialMode);
  }

  //*************************************
  AppInventor(int aRxPin, int aTxPin)  // SoftSerial
    : RemoteControl(rcAppInventor) {
    _bluetooth = new Bluetooth(aRxPin, aTxPin);
  }

  //*************************************
  AppInventor(EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rcAppInventor) {
    _bluetooth = new Bluetooth(aHardwareSerialMode);
  }

  //*************************************
  RemoteInput* GetControl(ERcControl aControl) {
    switch (aControl) {
      case rcJoystick1X:
        if (_channelRemoteInputs[0] == NULL) {
          _channelRemoteInputs[0] = new RemoteJoystickAxis(-200, 200, false);
        }
        return _channelRemoteInputs[0];
      case rcJoystick1Y:
        if (_channelRemoteInputs[1] == NULL) {
          _channelRemoteInputs[1] = new RemoteJoystickAxis(-120, 120, false);
        }
        return _channelRemoteInputs[1];
      case rcJoystick2X:
        if (_channelRemoteInputs[2] == NULL) {
          _channelRemoteInputs[2] = new RemoteJoystickAxis(-120, 120, false);
        }
        return _channelRemoteInputs[2];
      case rcJoystick2Y:
        if (_channelRemoteInputs[3] == NULL) {
          _channelRemoteInputs[3] = new RemoteJoystickAxis(-120, 120, false);
        }
        return _channelRemoteInputs[3];
    }
	return NULL;
  }

  //*************************************
  void Setup() {
    GetLog()->println("AI:S");

    for (int idx = 0; idx < APPINVENTOR_COMMANDBUFFER_SIZE; ++idx) {
      _commandBuffer[idx] = '\0';
    }

    RemoteControl::Setup();

    if (_bluetooth != NULL) {
      _bluetooth->Setup();
    }
  }

  //*************************************
  void Loop() {
    if (_bluetooth != NULL) {
      _bluetooth->Loop();
    }
    if (_bluetooth->DataReceived()) {
#ifdef LOG_LOOP_DEBUG
      GetLog()->printf("AI:L Recvd");
#endif
      strcat(_commandBuffer, _bluetooth->Data());
      ParseAndUpdateTelegram();
    }

    this->RemoteControl::Loop();
  }
};
#endif