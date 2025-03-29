//*****************************************************************
//* Class AppInventor - Header
//*
//* Logic of the AppInventor-RemoteControl (HandyApp)
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


#define APPINVENTOR_JOYSTICK_minX -180
#define APPINVENTOR_JOYSTICK_maxX 180
#define APPINVENTOR_JOYSTICK_minY -120
#define APPINVENTOR_JOYSTICK_maxY 120
#define APPINVENTOR_VrX_minY 0
#define APPINVENTOR_VrX_maxY 178
#define APPINVENTOR_COMMANDBUFFER_SIZE 100
#define APPINVENTOR_SLIDER_MIN -120
#define APPINVENTOR_SLIDER_MAX 120

#ifndef ARDUINO_MAX_PWM_OUT
  #define ARDUINO_MAX_PWM_OUT 255
#endif
  
#ifndef ARDUINO_MAX_PWM_IN
  #define ARDUINO_MAX_PWM_IN 1023
#endif

class AppInventor : public RemoteControl {
private:
  Bluetooth* _bluetooth;
  char _commandBuffer[APPINVENTOR_COMMANDBUFFER_SIZE + 1];
  Condition* _enableCondition = NULL;
  bool _communicationEnabled = false;

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
      GetLog()->println("AI:PT Buffer is empty");
#endif
      return;
    }
	else
	{
#ifdef LOG_LOOP		
      GetLog()->printf("AI:PT %s", _commandBuffer);		
#endif		
	}

    char* command = strtok(_commandBuffer, ",");
    if (command == NULL) 
	{
#ifdef LOG_LOOP_DEBUG
      GetLog()->println("AI:PT No command received");
#endif
      return;
    }

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("AI:PT %s Cd=%s", _commandBuffer, command);
#endif
    int cutLen = 1;
    switch (command[0]) {
      case 'D':     
      case 'E':      
        {
          char* xAxis = strtok(NULL, ",");
          if (xAxis != NULL) {
            _channelValue[rcJoystick1X] = atoi(xAxis);
            if (_channelRemoteInputs[rcJoystick1X] != NULL) {
              _channelRemoteInputs[rcJoystick1X]->SetMapValue(_channelValue[rcJoystick1X], APPINVENTOR_JOYSTICK_minX, APPINVENTOR_JOYSTICK_maxX);
            }
            char* yAxis = strtok(NULL, ",");
            if (yAxis != NULL) {
#ifdef LOG_LOOP_DEBUG
              GetLog()->printf("AI:PT Js X=%s Y=%s", xAxis, yAxis);
#endif
              _channelValue[rcJoystick1Y] = atoi(yAxis);
              if (_channelRemoteInputs[rcJoystick1Y] != NULL) {
                _channelRemoteInputs[rcJoystick1Y]->SetMapValue(_channelValue[rcJoystick1Y], APPINVENTOR_JOYSTICK_minY, APPINVENTOR_JOYSTICK_maxY);
              }
              cutLen = 4 + numberLen(_channelValue[rcJoystick1X]) + numberLen(_channelValue[rcJoystick1Y]);
            } else {
              cutLen = 3 + numberLen(_channelValue[rcJoystick1X]);
            }
          }
        }
        break;
      case 'F':      
        {
          char* xAxis = strtok(NULL, ",");
          if (xAxis != NULL) {
            _channelValue[rcJoystick2X] = atoi(xAxis);
            if (_channelRemoteInputs[rcJoystick2X] != NULL) {
              _channelRemoteInputs[rcJoystick2X]->SetMapValue(_channelValue[rcJoystick2X], APPINVENTOR_JOYSTICK_minX, APPINVENTOR_JOYSTICK_maxX);
            }
            char* yAxis = strtok(NULL, ",");
            if (yAxis != NULL) {
#ifdef LOG_LOOP_DEBUG
              GetLog()->printf("AI:PT Js X=%s Y=%s", xAxis, yAxis);
#endif
              _channelValue[rcJoystick2Y] = atoi(yAxis);
              if (_channelRemoteInputs[rcJoystick2Y] != NULL) {
                _channelRemoteInputs[rcJoystick2Y]->SetMapValue(_channelValue[rcJoystick2Y], APPINVENTOR_JOYSTICK_minY, APPINVENTOR_JOYSTICK_maxY);
              }
              cutLen = 4 + numberLen(_channelValue[rcJoystick2X]) + numberLen(_channelValue[rcJoystick2Y]);
            } else {
              cutLen = 3 + numberLen(_channelValue[rcJoystick2X]);
            }
          }
        }
        break;        
        
      case 'J':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcSwA] = atoi(value);
            if (_channelRemoteInputs[rcSwA] != NULL) {
              _channelRemoteInputs[rcSwA]->SetValue(_channelValue[rcSwA]);
            }
            cutLen = 3 + numberLen(_channelValue[rcSwA]);
          }          
        }
        break;        
        
      case 'K':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcSwB] = atoi(value);
            if (_channelRemoteInputs[rcSwB] != NULL) {
              _channelRemoteInputs[rcSwB]->SetValue(_channelValue[rcSwB]);
            }
            cutLen = 3 + numberLen(_channelValue[rcSwB]);
          }      
        }
        break;        
        
      case 'L':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcSwC] = atoi(value);
            if (_channelRemoteInputs[rcSwC] != NULL) {
              _channelRemoteInputs[rcSwC]->SetValue(_channelValue[rcSwC]);
            }
            cutLen = 3 + numberLen(_channelValue[rcSwC]);
          }          
        }
        break;        
        
      case 'M':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcSwD] = atoi(value);
            if (_channelRemoteInputs[rcSwD] != NULL) {
              _channelRemoteInputs[rcSwD]->SetValue(_channelValue[rcSwD]);
            }
            cutLen = 3 + numberLen(_channelValue[rcSwD]);
          }          
        }
        break; 
        
      case 'X':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcVrA] = atoi(value);
            if (_channelRemoteInputs[rcVrA] != NULL) {
              _channelRemoteInputs[rcVrA]->SetMapValue(_channelValue[rcVrA], APPINVENTOR_VrX_minY, APPINVENTOR_VrX_maxY);
            }
            cutLen = 3 + numberLen(_channelValue[rcVrA]);
          }      
        }
        break;        
        
      case 'Y':
        {
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcVrB] = atoi(value);
            if (_channelRemoteInputs[rcVrB] != NULL) {
              _channelRemoteInputs[rcVrB]->SetMapValue(_channelValue[rcVrB], APPINVENTOR_VrX_minY, APPINVENTOR_VrX_maxY);
            }
            cutLen = 3 + numberLen(_channelValue[rcVrB]);
          }            
        }
        break;        
        
      case 'A':
        // No connection monitoring is currently implemented. The LED on the HC06
        // lights up every second to see whether communication is taking place.
        cutLen = 2;
        break;
        
      case 'W':
        {
          // Obsolete: For compatiblity to old app only
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcJoystick2X] = atoi(value);
            if (_channelRemoteInputs[rcJoystick2X] != NULL) {
              _channelRemoteInputs[rcJoystick2X]->SetMapValue(_channelValue[rcJoystick2X], APPINVENTOR_SLIDER_MIN, APPINVENTOR_SLIDER_MAX);
            }
            cutLen = 3 + numberLen(_channelValue[rcJoystick2X]);
          }
        }
        break;
        
      case 'V':
        {
          // Obsolete: For compatiblity to old app only
          char* value = strtok(NULL, ",");
          if (value != NULL) {
            _channelValue[rcJoystick2Y] = atoi(value);
            if (_channelRemoteInputs[rcJoystick2Y] != NULL) {
              _channelRemoteInputs[rcJoystick2Y]->SetMapValue(_channelValue[rcJoystick2Y], APPINVENTOR_SLIDER_MIN, APPINVENTOR_SLIDER_MAX);
            }
            cutLen = 3 + numberLen(_channelValue[rcJoystick2Y]);
          }
        }
        break;   
        
      default:

#ifdef LOG_LOOP
        GetLog()->printf("AI:PT Unkown Cd recvd %02x", (uint8_t)command[0]);
#endif
        for (int idx = strlen(command); idx < APPINVENTOR_COMMANDBUFFER_SIZE; ++idx) {
          if (_commandBuffer[idx] == '\0') {
#ifdef LOG_LOOP_DEBUG
            GetLog()->printf("AI:PT Empting buffer %02x", (uint8_t)command[0]);
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
    GetLog()->printf("AI:PT CV[0..4] %d, %d, %d, %d, %d", _channelValue[0], _channelValue[1], _channelValue[2], _channelValue[3], _channelValue[4]);
    GetLog()->printf("AI:PT CV[5..9] %d, %d, %d, %d, %d", _channelValue[5], _channelValue[6], _channelValue[7], _channelValue[8], _channelValue[9]);
#endif
  }

protected:
  //*************************************
  bool DoSendMessage(const char* aMessage) 
  {
    return _bluetooth->SendMessage(aMessage);
  }

public:
#ifndef ARDUINO_ARCH_ESP32    
  //*************************************
  AppInventor(RemoteInput** aRemoteInputs, int aRxPin, int aTxPin)  // SoftSerial
    : RemoteControl(rtAppInventor, aRemoteInputs) 
  {
    // Hardware serial
    _bluetooth = new Bluetooth(aRxPin, aTxPin);
#ifdef MULTI_REMOTECONTROL			    
    _communicationEnabled = true;
#endif    
  }

  //*************************************
  AppInventor(int aRxPin, int aTxPin)  // SoftSerial
    : RemoteControl(rtAppInventor) 
  {
    _bluetooth = new Bluetooth(aRxPin, aTxPin);
#ifdef MULTI_REMOTECONTROL			    
    _communicationEnabled = true;
#endif    
  }
#endif

  //*************************************
  AppInventor(RemoteInput** aRemoteInputs, EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rtAppInventor, aRemoteInputs) 
  {
    // Hardware serial only
    _bluetooth = new Bluetooth(aHardwareSerialMode);
#ifdef MULTI_REMOTECONTROL			    
    _communicationEnabled = true;
#endif    
  }

  //*************************************
  AppInventor(EHardwareSerialMode aHardwareSerialMode)
    : RemoteControl(rtAppInventor) 
  {
    _bluetooth = new Bluetooth(aHardwareSerialMode);
#ifdef MULTI_REMOTECONTROL			    
    _communicationEnabled = true;
#endif    
  }
  
//*************************************
  AppInventor(EHardwareSerialMode aHardwareSerialMode, Condition* aConditionWhenEnabled)
    : RemoteControl(rtAppInventor) 
  {
#ifdef MULTI_REMOTECONTROL			    
    _communicationEnabled = false;
#endif    
     _enableCondition = aConditionWhenEnabled;
	 
    _bluetooth = new Bluetooth(aHardwareSerialMode);
  }

  //*************************************
  RemoteInput* getControl(ERcControl aControl) {
#ifdef LOG_SETUP_DEBUG    
    GetLog()->printf("AI:G Tp=%d", aControl);
#endif               
    
    switch (aControl) {
      case rcJoystick1X:
        if (_channelRemoteInputs[rcJoystick1X] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G J1X");
#endif                         
          _channelRemoteInputs[rcJoystick1X] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[rcJoystick1X];
      case rcJoystick1Y:
        if (_channelRemoteInputs[rcJoystick1Y] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G J1Y");
#endif                         
          _channelRemoteInputs[rcJoystick1Y] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[rcJoystick1Y];
      case rcJoystick2X:
        if (_channelRemoteInputs[rcJoystick2X] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G J2X");
#endif                                   
          _channelRemoteInputs[rcJoystick2X] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[rcJoystick2X];
      case rcJoystick2Y:
        if (_channelRemoteInputs[rcJoystick2Y] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G J2Y");
#endif                                   
          _channelRemoteInputs[rcJoystick2Y] = new RemoteJoystickAxis(-ARDUINO_MAX_PWM_OUT, ARDUINO_MAX_PWM_OUT, false);
        }
        return _channelRemoteInputs[rcJoystick2Y];
      case rcVrA:
        if (_channelRemoteInputs[rcVrA] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G VrA");
#endif                         
          _channelRemoteInputs[rcVrA] = new RemoteValue(0, ARDUINO_MAX_PWM_IN);
        }
        return _channelRemoteInputs[rcVrA];
      case rcVrB:
        if (_channelRemoteInputs[rcVrB] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G VrB");
#endif                         
          _channelRemoteInputs[rcVrB] = new RemoteValue(0, ARDUINO_MAX_PWM_IN);
        }
        return _channelRemoteInputs[rcVrB];
      case rcSwA:
        if (_channelRemoteInputs[rcSwA] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G SwA");
#endif                         
          _channelRemoteInputs[rcSwA] = new RemoteValue(0, 1);
        }
        return _channelRemoteInputs[rcSwA];
      case rcSwB:
        if (_channelRemoteInputs[rcSwB] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G SwB");
#endif                         
          _channelRemoteInputs[rcSwB] = new RemoteValue(0, 1); 
        }
        return _channelRemoteInputs[rcSwB];
      case rcSwC:
        if (_channelRemoteInputs[rcSwC] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("AI:G SwC");
#endif                         
          _channelRemoteInputs[rcSwC] = new RemoteValue(0, 2);
        }
        return _channelRemoteInputs[rcSwC];
      case rcSwD:
        if (_channelRemoteInputs[rcSwD] == NULL) {
#ifdef LOG_SETUP_DEBUG    
          GetLog()->println("FS:G SwD");
#endif                         
          _channelRemoteInputs[rcSwD] = new RemoteValue(0, 1);
        }
        return _channelRemoteInputs[rcSwD];        
    }
	return NULL;
  }

  //*************************************
  void Setup() {
#ifdef LOG_SETUP_DEBUG        
    GetLog()->println("AI:S");
#endif		  

    for (int idx = 0; idx < APPINVENTOR_COMMANDBUFFER_SIZE; ++idx) {
      _commandBuffer[idx] = '\0';
    }

    RemoteControl::Setup();

    if (_bluetooth != NULL) {		
      _bluetooth->Setup();
	  _bluetooth->Enable();
      
#ifdef LOG_SETUP_DEBUG        
      GetLog()->println("AI:S BT+");
#endif
	}
  }

  //*************************************
  void Loop() {  
    if (_enableCondition!=NULL)
	{
		if (_enableCondition->Check() != _communicationEnabled)
		{
			if (_enableCondition->Check() && !_communicationEnabled)
			{
			  _bluetooth->Enable();
              _communicationEnabled = true;
			}
			else if (!_enableCondition->Check() && _communicationEnabled)
			{
			  _bluetooth->Disable();
              _communicationEnabled = false;
			}
		}		
	}
	  
#ifdef MULTI_REMOTECONTROL			
  bool communicationEnabled = _communicationEnabled;
#else
  bool communicationEnabled = true;
#endif 
  
    if (communicationEnabled) {
      if (_bluetooth != NULL) {
        _bluetooth->Loop();
      }

      if (_bluetooth->DataReceived()) {
#ifdef LOG_LOOP_DEBUG
        GetLog()->println("AI:L Recvd");
#endif
        strcpy(_commandBuffer, _bluetooth->Data());
        while(_commandBuffer[0] != '\0')
        {
          ParseAndUpdateTelegram();
        }
      }

      this->RemoteControl::Loop();
    }
  }
};
#endif