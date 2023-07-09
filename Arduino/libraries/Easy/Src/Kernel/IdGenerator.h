//*****************************************************************
//* Class IdGenerator - Header
//*
//* Internal help class to generate a unique element id
//*****************************************************************
//* Sketch made Easy for Arduino -  Arduino quick and easy
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

#ifndef EASY_IDGENERATOR_H
#define EASY_IDGENERATOR_H

class IdGenerator {
private:
  static int _maxId;
public:
  //*************************************
  static int CreateId() {
    return ++_maxId;
  }

  //*************************************
  static void Check(int aId) {
    if (aId > _maxId) {
      _maxId = aId;
    }
  }
};

#endif
