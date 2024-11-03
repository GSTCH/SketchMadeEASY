//*****************************************************************
//* Class RemoteControl - Header
//*
//* Internal base class
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#ifndef EASY_REMOTECONTROL_H
#define EASY_REMOTECONTROL_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "RemoteInput.h"
#include "ControlManagerFactory.h"
#include <Math.h>

#define EASY_MAX_CHANNEL 10
#define EASY_MAX_MESSAGE_LEN 50
#define EASY_MIN_DISPLAY_TIME_MSEC 750

class RemoteControl{
private:

protected:
  int _channelValue[EASY_MAX_CHANNEL];
  RemoteInput* _channelRemoteInputs[EASY_MAX_CHANNEL];

  bool _connected = false;
  bool _connectionChanged = false;  

  char _lastMessage[EASY_MAX_MESSAGE_LEN + 1];
  unsigned long _lastMessageSent;
  ERemoteControlType _remoteControlType;

  //*************************************
  virtual bool DoSendMessage(const char* aMessage) 
  {
    return false;
  }

public:
  //*************************************
  RemoteControl(ERemoteControlType aRemoteControlType, RemoteInput** aRemoteInputs) {
#ifdef LOG_SETUP
    GetLog()->printf("RC:C Tp=%d RI(%d)", aRemoteControlType, sizeof(aRemoteInputs));
#endif

    // Any remote control needs no additional parameter.
    _remoteControlType = aRemoteControlType;
    _lastMessageSent = 0;

    for (int idx = 0; idx < EASY_MAX_CHANNEL; ++idx) {
      _channelValue[idx] = 0;
      _channelRemoteInputs[idx] = aRemoteInputs[idx];
#ifdef LOG_SETUP_DEBUG
      if (aRemoteInputs[idx] == NULL) {
        GetLog()->printf("RC:C Ids %d is NULL", idx);
      }
#endif
    }

    ControlManagerFactory::GetControlManager()->Set(this);
  }

  //*************************************
  RemoteControl(ERemoteControlType aRemoteControlType) {
#ifdef LOG_SETUP
    GetLog()->printf("RC:C Tp=%d", aRemoteControlType);
#endif

    // Any remote control needs no additional parameter.
    _remoteControlType = aRemoteControlType;
    _lastMessageSent = 0;

    for (int idx = 0; idx < EASY_MAX_CHANNEL; ++idx) {
      _channelValue[idx] = 0;
      _channelRemoteInputs[idx] = NULL;
    }

    ControlManagerFactory::GetControlManager()->Set(this);
  }

  //*************************************
  virtual void Setup() {}

  //*************************************
  virtual void Loop() {}

  //*************************************
  inline bool Connected() {
    return _connected;
  }

  //*************************************
  inline bool ConnectionChanged() {
    if (_connectionChanged) {
      _connectionChanged = false;
      return true;
    }

    return false;
  }

  //*************************************
  void SendMessage(const char* aMessage) {
    unsigned long currentTime = millis();
    if ((currentTime - _lastMessageSent) > EASY_MIN_DISPLAY_TIME_MSEC) {
      // In order not to overload the line and to give the operator the change to read a message, there is a time filter.
      if (strncmp(_lastMessage, aMessage, EASY_MAX_MESSAGE_LEN) != 0) {
        strncpy(_lastMessage, aMessage, EASY_MAX_MESSAGE_LEN);

        // Log the message to RemoteControl too
#ifdef LOG_LOOP
        GetLog()->printf("RC:SM User Ms='%s'", aMessage);
#endif
        // Sende Meldung an Handy
        if (DoSendMessage(aMessage)) {
          _lastMessageSent = currentTime;
        }
      }
    } else {
#ifdef LOG_LOOP
      GetLog()->printf("RC:SM !User Ms='%s'", aMessage);
#endif
    }
  }

  //*************************************
  virtual RemoteInput* getControl(ERcControl aControl) {
    return _channelRemoteInputs[aControl];
  }  
};

#endif