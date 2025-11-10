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

#ifndef EASY_FLYSKY_MINVALUE
#define EASY_FLYSKY_MINVALUE 1000
#endif 

#ifndef EASY_FLYSKY_MAXVALUE
#define EASY_FLYSKY_MAXVALUE 2000
#endif

#ifndef ARDUINO_MAX_PWM_OUT
#define ARDUINO_MAX_PWM_OUT 255
#endif

#ifndef ARDUINO_MAX_PWM_IN
#define ARDUINO_MAX_PWM_IN 1023
#endif


class FlySky : public RemoteControl {
private:
  IBusBM* _ibusRC;
  EHardwareSerialMode _serialMode;

  ERcCommunicationState _communicationState = csOff;

  inline void ConfigIBus(EHardwareSerialMode aHardwareSerialMode) {
    _serialMode = aHardwareSerialMode;
    _ibusRC = new IBusBM();
  }

protected:

public:
  // FlySky class is not able to communicate dynamically

  //*************************************
  FlySky(RemoteInput** aRemoteInputs, EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rtFlySky, aRemoteInputs) {
#ifdef LOG_SETUP
    GetLog()->println("FS:C1");

#endif
    ConfigIBus(aHardwareSerialMode);
  }

  //*************************************
  FlySky(EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rtFlySky)
  {
#ifdef LOG_SETUP_DEBUG
    GetLog()->println("FS:C2 in");
#endif

    ConfigIBus(aHardwareSerialMode);
  }

  //*************************************		  
  RemoteInput* getControl(ERcControl aControl) {
#ifdef LOG_SETUP_DEBUG    
    GetLog()->printf("FS:G Tp=%d", aControl);
#endif               

    switch (aControl) {
      case rcJoystick1X:
        if (_channelRemoteInputs[0] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G J1X");
#endif               
          _channelRemoteInputs[0] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[0];
      case rcJoystick1Y:
        if (_channelRemoteInputs[1] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G J1Y");
#endif                        
          _channelRemoteInputs[1] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[1];
      case rcJoystick2X:
        if (_channelRemoteInputs[2] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G J2X");
#endif                        
          _channelRemoteInputs[2] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[2];
      case rcJoystick2Y:
        if (_channelRemoteInputs[3] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G J2Y");
#endif                         
          _channelRemoteInputs[3] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[3];
      case rcVrA:
        if (_channelRemoteInputs[4] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G VrA");
#endif                         
          _channelRemoteInputs[4] = new RemoteValue(0, ARDUINO_MAX_PWM_IN);
        }
        return _channelRemoteInputs[4];
      case rcVrB:
        if (_channelRemoteInputs[5] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G VrB");
#endif                         
          _channelRemoteInputs[5] = new RemoteValue(0, ARDUINO_MAX_PWM_IN);
        }
        return _channelRemoteInputs[5];
      case rcSwA:
        if (_channelRemoteInputs[6] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G SwA");
#endif                         
          _channelRemoteInputs[6] = new RemoteValue(0, 1);
        }
        return _channelRemoteInputs[6];
      case rcSwB:
        if (_channelRemoteInputs[7] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G SwB");
#endif                         
          _channelRemoteInputs[7] = new RemoteValue(0, 1);
        }
        return _channelRemoteInputs[7];
      case rcSwC:
        if (_channelRemoteInputs[8] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G SwC");
#endif                         
          _channelRemoteInputs[8] = new RemoteValue(0, 2);
        }
        return _channelRemoteInputs[8];
      case rcSwD:
        if (_channelRemoteInputs[9] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G SwD");
#endif                         
          _channelRemoteInputs[9] = new RemoteValue(0, 1);
        }
        return _channelRemoteInputs[9];
    }

    return NULL;
  }

  //*************************************
  void Setup() {
#ifdef LOG_SETUP_DEBUG
    GetLog()->println("FS:S");
#endif

    switch (_serialMode) {
      case scHard:
        // SerialMonitor (Log) and bluetooth have conflics at Nano and Uno. Mega has three additional hardware serial channels.
        if (GetLog()->enabled()) {
          GetLog()->disable();
        }

        //Serial.begin(115200, SERIAL_8N1);
        _ibusRC->begin(Serial);
        _communicationState = csDisabled;
        break;
#if defined( __AVR_ATmega2560__) ||  defined(ARDUINO_ARCH_ESP32)
      case scHard1:
#ifdef LOG_SETUP
        GetLog()->println("FS:S HW1");
#endif		
        pinMode(19, INPUT_PULLUP);  // fix Serial1
        _ibusRC->begin(Serial1);
        _communicationState = csDisabled;
        break;
      case scHard2:
#ifdef LOG_SETUP	  
        GetLog()->println("FS:S HW2");
#endif		
        pinMode(17, INPUT_PULLUP);  // fix Serial2
        _ibusRC->begin(Serial2);
        _communicationState = csDisabled;
        break;
#endif  // __AVR_ATmega2560__ or ESP32
#if defined( __AVR_ATmega2560__)                    
      case scHard3:
#ifdef LOG_SETUP	  
        GetLog()->println("FS:S HW3");
#endif				
        _communicationState = csDisabled;
        _ibusRC->begin(Serial3);
        pinMode(15, INPUT_PULLUP);  // fix Serial3
        break;
#endif  // __AVR_ATmega2560__
    }

    // Wait for the receiver to receive data from the transmitter (transmitter needs to be turned on)
    // as the channel values all read 0 as long as the transmitter is turned off at boot time.
    // We do not want the car to drive full speed backwards out of control.0
    if (_communicationState == csDisabled)
    {
#ifdef LOG_SETUP
      GetLog()->println("FS:S Wait RC");
#endif

      while (_ibusRC->cnt_rec == 0) delay(100);
      _connected = true;
      _communicationState = csOn;


#ifdef LOG_SETUP
      GetLog()->println("FS:S RC ok");
#endif
    }
  }

  //*************************************
  void Loop()
  {
#ifdef LOG_LOOP_DEBUG
    GetLog()->println("FS:L");
#endif

    if (_ibusRC != NULL && _communicationState == csOn) {
      bool anyChanges = false;

      for (int idx = 0; idx < EASY_MAX_CHANNEL; idx++) {
        if (_channelRemoteInputs[idx] != NULL) {

          int newValue = _ibusRC->readChannel(idx);
          if (newValue != _channelValue[idx]) {
            _channelValue[idx] = newValue;
            anyChanges = true;

            if (_channelRemoteInputs[idx] != NULL) {
              _channelRemoteInputs[idx]->SetMapValue(_channelValue[idx], EASY_FLYSKY_MINVALUE, EASY_FLYSKY_MAXVALUE);
            }
          }
        }
      }

#ifdef LOG_LOOP
      if (anyChanges) {
        GetLog()->printf("FS:L J [%d] [%d] [%d] [%d]", _channelValue[0], _channelValue[1], _channelValue[2], _channelValue[3]);
        GetLog()->printf("FS:L S [%d] [%d] [%d] [%d] [%d] [%d]", _channelValue[4], _channelValue[5], _channelValue[6], _channelValue[7], _channelValue[8], _channelValue[9]);
      }
#endif

    }
  }
};

#endif