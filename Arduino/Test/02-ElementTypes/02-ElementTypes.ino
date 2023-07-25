//*****************************************************************
//* 02-ElementTypes
//*
//* No logic, Log only the ElementType numbers.
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Control with Arduino made quickly and easily
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

#define LOG
#include <Easy.h>

//*****************************************************************
void setup() {
  //((*** Initialize: Configure your sketch here....
  //  * TODO:
  //  * - Define inputs
  //  * - Define actuators
  //  * - Define Logic (create conditions and relations)
  GetLog()->printf("DigitalOutput   = %d", CreateElementId(EbtInput, EkiDigital, DIGITAL_INPUT_INDEX));
  GetLog()->printf("Switch2Position = %d", CreateElementId(EbtInput, EkiDigital, DIGITAL_SWITCH2POSITION_INDEX));
  GetLog()->printf("Switch3Position = %d", CreateElementId(EbtInput, EkiDigital, DIGITAL_SWITCH3POSITION_INDEX));
  GetLog()->printf("ToggleSwitch    = %d", CreateElementId(EbtInput, EkiDigital, DIGITAL_TOGGLESWITCH_INDEX));
  GetLog()->printf("LoopSwitch      = %d", CreateElementId(EbtInput, EkiDigital, DIGITAL_LOOPSWITCH_INDEX));
  GetLog()->printf("MonoFlop        = %d", CreateElementId(EbtInput, EkiDigital, DIGITAL_MONOFLOP_INDEX));
  GetLog()->printf("AnalogInput     = %d", CreateElementId(EbtInput, EkiAnalog, ANALOG_INPUT_INDEX));
  GetLog()->printf("JoystickAxis    = %d", CreateElementId(EbtInput, EkiAnalog, ANALOG_JOYSTICKAXIS_INDEX));
  GetLog()->printf("RemoteJobstickAxis   = %d", CreateElementId(EbtInput, EkiVirtual, VIRTUAL_JOYSTICKAXIS_INDEX));
  GetLog()->printf("RemoteValue     = %d", CreateElementId(EbtInput, EkiVirtual, VIRTUAL_VALUE_INDEX));
  GetLog()->printf("FixValue        = %d", CreateElementId(EbtInput, EkiHelper, INHELPER_FIXVALUE_INDEX));
  GetLog()->printf("Inverter        = %d", CreateElementId(EbtInput, EkiHelper, INHELPER_INVERTER_INDEX));
  GetLog()->printf("Timer           = %d", CreateElementId(EbtInput, EkiHelper, INHELPER_TIMER_INDEX));
  GetLog()->printf("Calculate       = %d", CreateElementId(EbtInput, EkiHelper, INHELPER_CALCULATE_INDEX));
  GetLog()->printf("IteratorValue   = %d", CreateElementId(EbtInput, EkiHelper, INHELPER_ITERATORVALUE_INDEX));
  GetLog()->printf("ConditionInput  = %d", CreateElementId(EbtInput, EkiLogic, LOGIC_CONDITIONINPUT_INDEX));
  GetLog()->printf("DependendInput  = %d", CreateElementId(EbtInput, EkiLogic, LOGIC_DEPENDENDINPUT_INDEX));
  GetLog()->printf("UltraSonicRangeFinder= %d", CreateElementId(EbtInput, EkiSensor, SENSOR_ULTRASONICRANGEFINDER_INDEX));
  GetLog()->printf("AnalogOutput    = %d", CreateElementId(EbtActuator, EkaDigital, DIGITAL_OUTPUT_INDEX));
  GetLog()->printf("JoystickCalibate= %d", CreateElementId(EbtActuator, EkaDigital, DIGITAL_JOYSTICK_CALIBRATE));
  GetLog()->printf("AnalogOutput    = %d", CreateElementId(EbtActuator, EkaAnalog, ANALOG_OUTPUT_INDEX));
  GetLog()->printf("Buzzer          = %d", CreateElementId(EbtActuator, EkaAnalog, ANALOG_BUZZER_INDEX));
  GetLog()->printf("Motor L298      = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_L298_INDEX));
  GetLog()->printf("Motor L9110     = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_L9110_INDEX));
  GetLog()->printf("Moptor I2C      = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_I2C_INDEX));
  GetLog()->printf("Motor Servo T1  = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT1_INDEX));
  GetLog()->printf("Motor Servo T1  = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOT2_INDEX));
  GetLog()->printf("Motor Servo PWM = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOPWM_INDEX));
  GetLog()->printf("Motor Servo I2C = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_SERVOI2C_INDEX));
  GetLog()->printf("Motor Stepper Rotate    = %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_STEPPERROTATE_INDEX));
  GetLog()->printf("Motor Stepper Rotate I2C= %d", CreateElementId(EbtActuator, EkaMotor, MOTOR_STEPPERROTATEI2C_INDEX));
  GetLog()->printf("Servo T1        = %d", CreateElementId(EbtActuator, EkaServo, SERVO_T1_INDEX));
  GetLog()->printf("Servo T2        = %d", CreateElementId(EbtActuator, EkaServo, SERVO_T2_INDEX));
  GetLog()->printf("Servo PWM       = %d", CreateElementId(EbtActuator, EkaServo, SERVO_PWM_INDEX));
  GetLog()->printf("Servo I2C       = %d", CreateElementId(EbtActuator, EkaServo, SERVO_I2C_INDEX));
  GetLog()->printf("Stepper Position     = %d", CreateElementId(EbtActuator, EkaServo, SERVO_STEPPERPOSITION_INDEX));
  GetLog()->printf("Stepper Position I2C = %d", CreateElementId(EbtActuator, EkaServo, SERVO_STEPPERPOSITIONI2C_INDEX));
  GetLog()->printf("EndcoderMotor L298   = %d", CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L298_INDEX));
  GetLog()->printf("EndcoderMotor L9110  = %d", CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_L9110_INDEX));
  GetLog()->printf("EndcoderMotor I2C    = %d", CreateElementId(EbtActuator, EkaEncoderMotor, ENCODERMOTOR_I2C_INDEX));
  GetLog()->printf("ActuatorCollection   = %d", CreateElementId(EbtActuator, EkaHelper, OUTHELPER_ACTUATORCOLLECTION_INDEX));
  GetLog()->printf("Relation1to1 = %d", CreateElementId(EbtRelation, EkrCompare, COMPARE_1TO1_INDEX));
  GetLog()->printf("CrawlerSteering = %d", CreateElementId(EbtRelation, EkrCompare, DIFFERENTIAL_STEARING_INDEX));
  GetLog()->printf("CompareCondition     = %d", CreateElementId(EbtCondition, EkcCompare, CONDITION_COMPARE_INDEX));
  GetLog()->printf("LogicCondition  = %d", CreateElementId(EbtCondition, EkcCompare, CONDITION_LOGIC_INDEX));
  GetLog()->printf("ElseCondition   = %d", CreateElementId(EbtCondition, EkcCompare, CONDITION_ELSE_INDEX));
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
