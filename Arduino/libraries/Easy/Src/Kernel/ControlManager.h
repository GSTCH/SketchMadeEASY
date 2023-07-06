//*****************************************************************
//* Class ControlManager - Header
//*
//* Internal class.
//* 
//* Usings:
//* - LinkedList by Ivan Seidel.
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

#ifndef EASY_CONTROLMANAGER_H
#define EASY_CONTROLMANAGER_H

#include <LinkedList.h>
#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"

#include "RemoteControl.h"
#include "Relation.h"
#include "Condition.h"
#include "Input.h"
#include "Actuator.h"
#include "ControlManagerBase.h"

class ControlManager : public ControlManagerBase {
protected:
  LinkedList<Input*>* _realInputs;
  LinkedList<Input*>* _toolInputs;
  LinkedList<Condition*>* _conditions;
  LinkedList<Input*>* _logicInputs;
  LinkedList<Relation*>* _relations;
  LinkedList<Actuator*>* _actuators;
#ifdef MULTI_REMOTECONTROL
  LinkedList<RemoteControl*>* _remoteControls;
#else
  RemoteControl* _remoteControl;
#endif  
  Element* Get(int aId);

public:
  ControlManager();
  void Setup();
  void Loop();
  void Add(Relation* aRelation);
  void Add(Input* aInput);
  void Add(Actuator* aActuator);
  void Add(Condition* aCondition);
  void Set(RemoteControl* aRemoteControl);
};
#endif
