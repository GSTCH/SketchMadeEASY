//*****************************************************************
//* Main include
//* Include this, when using any of the classes of tihs library.
///*****************************************************************
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

// Check this file e.g. to activate Logging, ...
#include "Common\BuildDefinition.h"

// Interals, direct included
/*
#include "Common\Types.h"
#include "Kernel\ElementType.h"
#include "Kernel\IdGenerator.h"
#include "Kernel\Element.h"
#include "Kernel\ControlManagerBase.h"
#include "Kernel\ControlManager.h"
#include "Kernel\ControlManagerFactory.h"
#include "Kernel\Input.h"
#include "Kernel\Actuator.h"
#include "Kernel\Condition.h"
#include "Kernel\Relation.h"
#include "Kernel\RemoteInput.h"
#include "Kernel\RemoteControl.h"
#include "Kernel\AdafruitI2cShield.h"
#include "Kernel\AdafruitShield.h"
#include "Kernel\I2cBus.h"
#include "Kernel\MotorBase.h"
#include "Kernel\MotorShieldBase.h"
#include "Kernel\MotorShieldAdafruitV2.h"
#include "Kernel\MotorShieldL298.h"
#include "Kernel\MotorShieldL9110.h"
#include "Kernel\MotorShieldServo360I2C.h"
#include "Kernel\MotorShieldServo360Pwm.h"
#include "Kernel\MotorShieldServo360T1.h"
#include "Kernel\MotorShieldServo360T2.h"
#include "Kernel\MotorShieldStepperRotate.h"
#include "Kernel\MotorShieldStepperRotateI2C.h"
#include "Common\ActuatorCollectionItem.h"
#include "Kernel\Bluetooth.h"
*/

#include "Common\Log.h"

// Phyisical inputs digital
#include "Input\DigitalInput.h"
#include "Input\Switch2Position.h"
#include "Input\Switch3Position.h"
#include "Input\ToggleSwitch.h"
#include "Input\LoopSwitch.h"
#include "Input\MonoFlop.h"
// Phyisical inputs analog
#include "Input\VariableInput.h"
#include "Input\JoystickAxis.h"
// Logic inputs
#include "Input\FixValue.h"
#include "Input\Inverter.h"
#include "Input\Timer.h"
#include "Input\IteratorValue.h"
#include "Input\ConditionInput.h"

// Phyisical actuator
#include "Actuator\DigitalOutput.h"
#include "Actuator\VariableOutput.h"
#include "Actuator\MotorI2C.h"
#include "Actuator\MotorL298.h"
#include "Actuator\MotorL9110.h"
#include "Actuator\MotorServo360I2C.h"
#include "Actuator\MotorServo360Pwm.h"
#include "Actuator\MotorServo360T1.h"
#include "Actuator\MotorServo360T2.h"
#include "Actuator\MotorStepperRotate.h"
#include "Actuator\MotorStepperRotateI2C.h"
// Logic actuator
#include "Actuator\ActuatorCollection.h"

// Relations
#include "Relation\Relation1to1.h"

// Conditions
#include "Condition\CompareCondition.h"
#include "Condition\LogicCondition.h"

//RemoteControl
#include "RemoteControl\FlySky.h"
#include "RemoteControl\AppInventor.h"
#include "RemoteControl\RemoteValue.h"
#include "RemoteControl\RemoteJoystickAxis.h"