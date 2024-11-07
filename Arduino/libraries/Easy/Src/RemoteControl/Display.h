//*****************************************************************
//* Class Display - Header
//*
//* Display support LVGL and TFT_eSPI
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

#ifndef EASY_DISPLAY_H
#define EASY_DISPLAY_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Types.h"
#include "..\Kernel\RemoteControl.h"
#include <TFT_eSPI.h>
#include <lvgl.h>


class Display : RemoteControl {
private:
  //*************************************
  uint16_t _screenWidth;
  uint16_t _screenHeight;
  uint16_t _colorDepth;
  uint16_t _calData[5];
  
  lv_disp_draw_buf_t* _drawBuffer;
  lv_disp_drv_t* _displayDrviver;
  lv_color_t* _buffer1;
  lv_indev_drv_t* _indevDriver;
 
protected:
  //*************************************
  bool DoSendMessage(const char* aMessage);


public:
  //*************************************
  Display(EDisplayType aDisplayType);
  void Setup();
  void Loop();

  static TFT_eSPI* Tft;
  static uint16_t TouchX;
  static uint16_t TouchY;  
};

#endif