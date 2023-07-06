//*****************************************************************
//* Struct SElementType - Implementation
//*
//* Internal base class defines the unique ID of an element.
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

#include "ElementType.h"

SElementType CreateElementId(EElementBaseType aBaseType, EElementKind aKind, int aIndex)
{
  SElementType elementType;
  elementType.BaseType = (byte)aBaseType;
  elementType.Kind = (byte)aKind;
  elementType.Index = aIndex;

  return elementType;
}
