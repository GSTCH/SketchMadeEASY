//*****************************************************************
//* Struct SElementType - Header
//*
//* Internal base class defins the unique ID of an element.
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

#ifndef EASY_SELEMENTTYPE_H
#define EASY_SELEMENTTYPE_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"


// Indexes for EkiDigital
#define DIGITAL_INPUT_INDEX 1
#define DIGITAL_SWITCH2POSITION_INDEX 2
#define DIGITAL_SWITCH3POSITION_INDEX 3
#define DIGITAL_TOGGLESWITCH_INDEX 4
#define DIGITAL_LOOPBUTTON_INDEX 5
#define DIGITAL_MONOFLOP_INDEX 6

// Indexes for EkinAalog
#define ANALOG_INPUT_INDEX 1
#define ANALOG_JOYSTICKAXIS_INDEX 2

// Indexes for EkiVirtual
#define VIRTUAL_JOYSTICKAXIS_INDEX 1
#define VIRTUAL_VALUE_INDEX 2

// Indexes for EkiHelper
#define INHELPER_FIXVALUE_INDEX 1
#define INHELPER_INVERTER_INDEX 2
#define INHELPER_TIMER_INDEX 3
#define INHELPER_CALCULATE_INDEX 4
#define INHELPER_ITERATORVALUE_INDEX 5
#define INHELPER_INPUTSELECTEDVALUE_INDEX 6

// Indexes of EkiLogic
#define LOGIC_CONDITIONINPUT_INDEX 1

// Indexes of EkiSensor
#define SENSTOR_ULTRASONICRANGEFINDER_INDEX 1

// Indexes for EkoDigital
#define DIGITAL_OUTPUT_INDEX 1
#define DIGITAL_JOYSTICK_CALIBRATE 2

// Indexes for EkoAnalog
#define ANALOG_OUTPUT_INDEX 1
#define ANALOG_BUZZER_INDEX 2

// Indexes for EkoMotor
#define MOTOR_L298_INDEX 1
#define MOTOR_L9110_INDEX 2
#define MOTOR_I2C_INDEX 3
#define MOTOR_SERVOT1_INDEX 4
#define MOTOR_SERVOT2_INDEX 5
#define MOTOR_SERVOPWM_INDEX 6
#define MOTOR_SERVOI2C_INDEX 7
#define MOTOR_STEPPERROTATE_INDEX 8

// Indexes for EkoEncoderMotor
#define ENCODERMOTOR_L298_INDEX 1
#define ENCODERMOTOR_L9110_INDEX 2
#define ENCODERMOTOR_I2C_INDEX 3

// Indexes for EkoServo
#define SERVO_T1_INDEX 1
#define SERVO_T2_INDEX 2
#define SERVO_PWM_INDEX 3
#define SERVO_I2C_INDEX 4
#define SERVO_STEPPERPOSITION_INDEX 5
#define SERVO_STEPPERPOSITIONI2C_INDEX 6

// Indexes of EkoHelper
#define OUTHELPER_ACTUATORCOLLECTION_INDEX 1

// Indexes of EkcCondition
#define CONDITION_COMPARE_INDEX 1
#define CONDITION_LOGIC_INDEX 2
#define CONDITION_ELSE_INDEX 3

// Indexes of EkrRelations
#define COMPARE_1TO1_INDEX 1
#define DIFFERENTIAL_STEARING_INDEX 2

enum EElementBaseType  {
  EbtInput = 0,
  EbtActuator = 1,
  EbtRelation = 2,
  EbtCondition = 3,
};

enum EElementKind {
  EkiDigital = 1,
  EkiAnalog = 2,
  EkiVirtual = 3,
  EkiHelper = 4,
  EkiLogic = 5,
  EkiSensor = 6,
  
  EkaDigital = 1,
  EkaAnalog = 2,
  EkaMotor = 3,
  EkaServo = 4,
  EkaEncoderMotor = 5,
  EkaHelper=6,

  EkrCompare = 1,
  EkrLogic = 2,

  EkcCompare = 1,
  EkcLogic = 2,
};

// This struct reperesent a bit coded number. Created with CreateElementId() function
struct SElementType
{
  int BaseType: 2;
  int Kind: 8;
  int Index: 6;

#ifdef LOG
  char* Dump(char* aBuffer)
  {    
    sprintf( aBuffer, "BT=%d, Kind=%d, Idx=%d", BaseType, Kind, Index);
    return aBuffer;
  }
#endif // LOG  
};


SElementType CreateElementId(EElementBaseType aBaseType, EElementKind aKind, int aIndex);

#endif
