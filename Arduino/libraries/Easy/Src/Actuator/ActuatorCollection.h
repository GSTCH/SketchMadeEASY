//*****************************************************************
//* Class ActuatorCollection - Header
//*
//*  Helper class when a relation should act multiple Actuators.
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

#ifndef EASY_ACTUATORCOLLECTION_H
#define EASY_ACTUATORCOLLECTION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Actuator.h"
#include "..\Common\ActuatorCollectionItem.h"
#include <LinkedList.h>

class ActuatorCollection : public Actuator {
private:
  LinkedList<ActuatorCollectionItem*>* _actuators;

public:
  //*************************************
  ActuatorCollection(LinkedList<ActuatorCollectionItem*>* aActuators)
    : Actuator(CreateElementId(EbtActuator, EkaHelper, OUTHELPER_ACTUATORCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=%d", _id, aActuators->size());
#endif

    _actuators = new LinkedList<ActuatorCollectionItem*>();

    for (int i = 0; i < aActuators->size(); ++i) {
      ActuatorCollectionItem* actuator = aActuators->get(i);
      _actuators->add(actuator);
    }
  }

  //*************************************
  ActuatorCollection(Actuator* aActuator1, Input* aActuatorParameter1, Actuator* aActuator2, Input* aActuatorParameter2)
    : Actuator(CreateElementId(EbtActuator, EkaHelper, OUTHELPER_ACTUATORCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=2", _id);
#endif

    _actuators = new LinkedList<ActuatorCollectionItem*>();
    _actuators->add(new ActuatorCollectionItem(aActuator1, aActuatorParameter1));
    _actuators->add(new ActuatorCollectionItem(aActuator2, aActuatorParameter2));
  }

  //*************************************
  ActuatorCollection(Actuator* aActuator1, Input* aActuatorParameter1, Actuator* aActuator2, Input* aActuatorParameter2, Actuator* aActuator3, Input* aActuatorParameter3)
    : Actuator(CreateElementId(EbtActuator, EkaHelper, OUTHELPER_ACTUATORCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=3", _id);
#endif

    _actuators = new LinkedList<ActuatorCollectionItem*>();
    _actuators->add(new ActuatorCollectionItem(aActuator1, aActuatorParameter1));
    _actuators->add(new ActuatorCollectionItem(aActuator2, aActuatorParameter2));
    _actuators->add(new ActuatorCollectionItem(aActuator3, aActuatorParameter3));
  }

  //*************************************
  ActuatorCollection(Actuator* aActuator1, Input* aActuatorParameter1, Actuator* aActuator2, Input* aActuatorParameter2, Actuator* aActuator3, Input* aActuatorParameter3, Actuator* aActuator4, Input* aActuatorParameter4)
    : Actuator(CreateElementId(EbtActuator, EkaHelper, OUTHELPER_ACTUATORCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=4", _id);
#endif
    _actuators = new LinkedList<ActuatorCollectionItem*>();
    _actuators->add(new ActuatorCollectionItem(aActuator1, aActuatorParameter1));
    _actuators->add(new ActuatorCollectionItem(aActuator2, aActuatorParameter2));
    _actuators->add(new ActuatorCollectionItem(aActuator3, aActuatorParameter3));
    _actuators->add(new ActuatorCollectionItem(aActuator4, aActuatorParameter4));
  }
  
   //*************************************
  ActuatorCollection(Actuator* aActuator1, Input* aActuatorParameter1, Actuator* aActuator2, Input* aActuatorParameter2, Actuator* aActuator3, Input* aActuatorParameter3, Actuator* aActuator4, Input* aActuatorParameter4, Actuator* aActuator5, Input* aActuatorParameter5)
    : Actuator(CreateElementId(EbtActuator, EkaHelper, OUTHELPER_ACTUATORCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=5", _id);
#endif
    _actuators = new LinkedList<ActuatorCollectionItem*>();
    _actuators->add(new ActuatorCollectionItem(aActuator1, aActuatorParameter1));
    _actuators->add(new ActuatorCollectionItem(aActuator2, aActuatorParameter2));
    _actuators->add(new ActuatorCollectionItem(aActuator3, aActuatorParameter3));
    _actuators->add(new ActuatorCollectionItem(aActuator4, aActuatorParameter4));
	_actuators->add(new ActuatorCollectionItem(aActuator5, aActuatorParameter5));
  } 

  //*************************************
  void Setup() {
    for (int i = 0; i < _actuators->size(); ++i) {
      ActuatorCollectionItem* actuator = _actuators->get(i);
      actuator->Setup();
    }
  }

  //*************************************
  void Loop() {
    for (int i = 0; i < _actuators->size(); ++i) {
      ActuatorCollectionItem* actuator = _actuators->get(i);
      actuator->Loop();
    }
  }

  //*************************************
  void Act(Input* aInput) {
    for (int i = 0; i < _actuators->size(); ++i) {
      ActuatorCollectionItem* actuator = _actuators->get(i);
      actuator->Act();
    }
  }
};

#endif
