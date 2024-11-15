//*****************************************************************
//* Types 
//* 
//* Common definitions, types, enums, consts, ... 
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Arduino quick and easy
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
#ifndef EasyTypes_h
#define EasyTypes_h

#include <stdint.h>

//*** Const and Defines
#define EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC 50

//*** Types
typedef uint8_t byte;

//*** Enums
enum ECompareOperator {
  OpEQ = 1,
  OpGT = 2,
  OpLT = 3,
  OpNEQ = 4,
  OpGTE = 5,
  OpLTE = 6,
};

enum ETurnDirection { moStop = 0,
                      moForward = 1,
                      moBackward = 2 };

enum EMotorInterfaceType { miFunction = 0,
                           miDriver = 1,
                           miFull2Wire = 2,
                           miFull3Wire = 3,
                           miFull4Wire = 4,
                           miHalf3Wire = 6,
                           miHalf4Wire = 8 };

enum EStepType { stSingle,
                 stDouble,
                 stInterleave,
                 stMicrostepping };

enum ERemoteControlType { rtAppInventor,
                          rtFlySky,
                          rtDisplay };

enum EHardwareSerialMode { scHard,
                           scHard1,
                           scHard2,
                           scHard3 };

enum ECycleMode { cmMin2Max_Min2Max = 0,
                  cmMin2Max2Min = 1 };

enum EInitializeMode { spNone = 0,
                       spForward = 1,
                       spBackward = 2 };

enum EStepStyle {
  ssSingle = 1,
  ssDouble = 2,
  ssInterleave = 3,
  ssMicrostep = 4
};

enum ESwitchResistoreMode {
  smPullDownInternal = 0,
  smPullDownExternal = 1,
  smPullUpExternal = 2,
#ifdef ARDUINO_ARCH_ESP32
  smPullUpInternal = 3,
#endif  
};

enum ERcControl { rcJoystick1X = 0, // JobstickAxis1X
                  rcJoystick1Y = 1, // JobstickAxis1Y
                  rcJoystick2X = 2, // JobstickAxis2X
                  rcJoystick2Y = 3, // JobstickAxis2Y
                  rcVrA = 4,        // Poti1
                  rcVrB = 5,        // Poti2
                  rcSwA = 6,        // Switch1, 2 Position
                  rcSwB = 7,        // Switch2, 2 Position
                  rcSwC = 8,        // Switch3, 3 Position
                  rcSwD = 9 };      // Switch4, 2 Position
					 
enum ERcCommunicationState {
  csOff = 0,
  csOn = 1,
  csDisabled = 2
};

enum EDisplayType { 
  ttILI9341_24in = 1, 
  ttILI9341_28in = 2, 
  ttILI9341_35in = 3 
};

#endif