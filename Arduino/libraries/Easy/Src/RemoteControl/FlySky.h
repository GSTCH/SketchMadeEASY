//*****************************************************************
//* Class FlySky - Header
//*
//* Logic of the FlySky FS-i6X-RemoteControl. 
//* With only change settings, it's support up to 14 channels.
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

#ifndef FlySky_h
#define FlySky_h

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\RemoteControl.h"
#include "..\Kernel\Bluetooth.h"
#include "RemoteValue.h"
#include "RemoteJoystickAxis.h"
#include <IBusBM.h>
#include <Arduino.h>

#define EASY_FLYSKY_MINVALUE 1000
#define EASY_FLYSKY_MAXVALUE 2000


class FlySky : public RemoteControl {
private:
  IBusBM* _ibusRC;
  EHardwareSerialMode _serialMode;

  inline void ConfigIBus(EHardwareSerialMode aHardwareSerialMode) {
    _serialMode = aHardwareSerialMode;
    _ibusRC = new IBusBM();
  }
  
protected:

public:
  //*************************************
  FlySky(RemoteInput** aRemoteInputs, EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rcAppInventor, aRemoteInputs) {
#ifdef LOG_SETUP
    GetLog()->printf("FS:C1");
#endif
    for (int idx = 0; idx < EASY_MAX_CHANNEL; idx++) {
      _channelRemoteInputs[idx] = aRemoteInputs[idx];
      _channelValue[idx] = 0;
    }

    ConfigIBus(aHardwareSerialMode);
  }

  //*************************************
  FlySky(EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rcAppInventor) {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("FS:C2 in");
#endif
    for (int idx = 0; idx < EASY_MAX_CHANNEL; idx++) {
      _channelRemoteInputs[idx] = NULL;
      _channelValue[idx] = 0;
    }

    ConfigIBus(aHardwareSerialMode);
  }

  //*************************************
  RemoteInput* getControl(ERcControl aControl) {
    switch (aControl) {
      case rcJoystick1X:
        if (_channelRemoteInputs[0] == NULL) {
          _channelRemoteInputs[0] = new RemoteJoystickAxis(-255, 255, false);
        }
        return _channelRemoteInputs[0];
      case rcJoystick1Y:
        if (_channelRemoteInputs[1] == NULL) {
          _channelRemoteInputs[1] = new RemoteJoystickAxis(-255, 255, false);
        }
        return _channelRemoteInputs[1];
      case rcJoystick2X:
        if (_channelRemoteInputs[2] == NULL) {
          _channelRemoteInputs[2] = new RemoteJoystickAxis(-255, 255, false);
        }
        return _channelRemoteInputs[2];
      case rcJoystick2Y:
        if (_channelRemoteInputs[3] == NULL) {
          _channelRemoteInputs[3] = new RemoteJoystickAxis(-255, 255, false);
        }
        return _channelRemoteInputs[3];
      case rcVRA:
        if (_channelRemoteInputs[4] == NULL) {
          _channelRemoteInputs[4] = new RemoteValue(0, 255);
        }
        return _channelRemoteInputs[4];
      case rcVRB:
        if (_channelRemoteInputs[5] == NULL) {
          _channelRemoteInputs[5] = new RemoteValue(0, 255);
        }
        return _channelRemoteInputs[5];
      case rcSwA:
        if (_channelRemoteInputs[6] == NULL) {
          _channelRemoteInputs[6] = new RemoteValue(0, 1);  // SWRA
        }
        return _channelRemoteInputs[6];
      case rcSwB:
        if (_channelRemoteInputs[7] == NULL) {
          _channelRemoteInputs[7] = new RemoteValue(0, 1);  // SWRB
        }
        return _channelRemoteInputs[7];
      case rcSwC:
        if (_channelRemoteInputs[8] == NULL) {
          _channelRemoteInputs[8] = new RemoteValue(0, 2);  // SWRC
        }
        return _channelRemoteInputs[8];
      case rcSwD:
        if (_channelRemoteInputs[9] == NULL) {
          _channelRemoteInputs[9] = new RemoteValue(0, 1);  // SWRD
        }
        return _channelRemoteInputs[9];
    }
  }

  //*************************************
  void Setup() {
    GetLog()->println("FS:S");

#ifdef LOG_SETUP_DEBUG
    GetLog()->println("FS:S");
#endif

    switch (_serialMode) {
      case scHard:
        _ibusRC->begin(Serial);
        break;
#ifdef __AVR_ATmega2560__
      case scHard1:
        GetLog()->println("FS:S HW1");
        pinMode(19, INPUT_PULLUP);  // fix Serial1
        _ibusRC->begin(Serial1);
        break;
      case scHard2:
        GetLog()->println("FS:S HW2");

        pinMode(17, INPUT_PULLUP);  // fix Serial2
        _ibusRC->begin(Serial2);
        break;
      case scHard3:
        GetLog()->println("FS:S HW3");

        pinMode(15, INPUT_PULLUP);  // fix Serial3
        _ibusRC->begin(Serial3);
        break;
#endif  // __AVR_ATmega2560__
    }

    // Wait for the receiver to receive data from the transmitter (transmitter needs to be turned on)
    // as the channel values all read 0 as long as the transmitter is turned off at boot time.
    // We do not want the car to drive full speed backwards out of control.0
#ifdef LOG_SETUP
    GetLog()->println("FS:S Wait RC");
#endif
    while (_ibusRC->cnt_rec == 0) delay(100);
    _connected = true;

#ifdef LOG_SETUP
    GetLog()->println("FS:S RC ok");
#endif
  }

  //*************************************
  void Loop() {
#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("FS:L");
#endif

    if (_ibusRC != NULL) {
      bool changed = false;

      for (int idx = 0; idx < EASY_MAX_CHANNEL; idx++) {
        if (_channelRemoteInputs[idx] != NULL) {

          int newValue = _ibusRC->readChannel(idx);
          if (newValue != _channelValue[idx]) {
            _channelValue[idx] = newValue;
            changed = true;
          }

          if (_channelRemoteInputs[idx] != NULL) {
            _channelRemoteInputs[idx]->SetMapValue(_channelValue[idx], EASY_FLYSKY_MINVALUE, EASY_FLYSKY_MAXVALUE);
          }
        }
      }

#ifdef LOG_LOOP
      if (changed) {
        GetLog()->printf("FS:L J [%d] [%d] [%d] [%d]", _channelValue[0], _channelValue[1], _channelValue[2], _channelValue[3]);
        GetLog()->printf("FS:L S [%d] [%d] [%d] [%d] [%d] [%d]", _channelValue[4], _channelValue[5], _channelValue[6], _channelValue[7], _channelValue[8], _channelValue[9]);
      }
#endif
    }
  }
};

#endif