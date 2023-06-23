//*****************************************************************
//* Types 
//* 
//* Common definitions, types, enums, consts, ... 
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Arduino quick and easy
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
#ifndef EasyTypes_h
#define EasyTypes_h

#include <stdint.h>

//*** Const and Defines
#define EASY_DEFAULT_DEBOUNCE_TIME_MILLI_SEC 50

//*** Types
typedef uint8_t byte;

//*** Enums
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

enum ERemoteControlType { rcAppInventor,
                          rcFlySky };

enum EHardwareSerialMode { scHard,
                           scHard1,
                           scHard2,
                           scHard3 };

enum ECycleMode { cmMin2Max_Min2Max,
                  cmMin2Max2Min };

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
};

#endif