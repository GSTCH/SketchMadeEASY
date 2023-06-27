//*****************************************************************
//* Class ControlManagerBase - Header
//*
//* Internal class
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

#include "..\Common\BuildDefinition.h" // has to be the first 

#ifndef EASY_CONTROLMANAGERBASE_H
#define EASY_CONTROLMANAGERBASE_H

// Prefent circular references/includes and define only the class as a type
class Input;
class Actuator;
class Relation;
class Condition;
class RemoteControl;

class ControlManagerBase
{
  public:
    ControlManagerBase() {}
    virtual void Setup() {}
    virtual void Loop() {}
    virtual void Add(Relation* aRelation) {}
    virtual void Add(Input* aInput) {}
    virtual void Add(Actuator* aActuator) {}
    virtual void Add(Condition *aCondition) {}
    virtual void Set(RemoteControl* aRemoteControl ) {}
};
#endif
