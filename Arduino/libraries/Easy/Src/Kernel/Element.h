//*****************************************************************
//* Class CElement - Header
//*
//* The internal base class
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

#ifndef EASY_ELEMENT_H
#define EASY_ELEMENT_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Common\Log.h"
#include "ElementType.h"
#include "IdGenerator.h"

class Element {
private:
  //*************************************
  void Init(int aId, struct SElementType aElementType) {
    _id = aId;
    _type = aElementType;

#ifdef LOG_SETUP
    GetLog()->printf("E(%d):C Tp=%d", _id, _type);
#endif
  }

protected:
  int _id;             // READONLY!
  SElementType _type;  // READONLY!

public:
  //*************************************
  Element(struct SElementType aElementType) {
    Init(IdGenerator::CreateId(), aElementType);
  }

  //*************************************
  Element(int aId, struct SElementType aElementType) {
    IdGenerator::Check(aId);
    Init(aId, aElementType);
  }

  //*************************************
  virtual void Setup() {}

  //*************************************
  virtual void Loop() {}

  //*************************************
  inline int GetId() {
    return _id;
  }

  //*************************************
  inline EElementBaseType GetBaseType() {
    return (EElementBaseType)_type.BaseType;
  }

  //*************************************
  inline EElementKind GetKind() {
    return (EElementKind)_type.Kind;
  }

  //*************************************
  inline int GetIndex() {
    return _type.Index;
  }
};

#endif
