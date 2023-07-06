//*****************************************************************
//* Class Relation - Header
//*
//* Internal base class
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

#ifndef EASY_RELATION_H
#define EASY_RELATION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "Condition.h"
#include "Element.h"
#include "ControlManagerFactory.h"

class Relation : public Element {
private:
  //*************************************
  void init(Condition* aCondition) {
    _condition = aCondition;
    ControlManagerFactory::GetControlManager()->Add(this);
  }

protected:
  Condition* _condition;

public:
  //*************************************
#ifdef CREATE_ID_MANUALLY  
  Relation(int aId, struct SElementType aElementType, Condition* aCondition)
    : Element(aId, aElementType) {
    init(aCondition);
  }
#endif

  //*************************************
  Relation(struct SElementType aElementType, Condition* aCondition)
    : Element(aElementType) {
    init(aCondition);
  }
};
#endif
