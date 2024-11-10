//*****************************************************************
//* Class Display - Header
//*
//* Display support LVGL and TFT_eSPI
//* 
//* https://docs.lvgl.io/master/index.html
//*
//* Draw a GUI e.g. with SquarelLine Studio and connect it with 
//* this class to Sketch Made Easy
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

#ifdef ARDUINO_ARCH_ESP32

#include "Display.h"

//************************************* C Code


void DisplayFlash(lv_disp_drv_t* aDisplay, const lv_area_t* aArea, lv_color_t* aColorP)
{
  uint32_t w = (aArea->x2 - aArea->x1 + 1);
  uint32_t h = (aArea->y2 - aArea->y1 + 1);

  Display::Tft->startWrite();
  Display::Tft->setAddrWindow(aArea->x1, aArea->y1, w, h);
  Display::Tft->pushColors((uint16_t*)&aColorP->full, w * h, true);
  Display::Tft->endWrite();

  lv_disp_flush_ready(aDisplay);
}

void ReadTouchpad(lv_indev_drv_t* indev_driver, lv_indev_data_t* aData)
{
  bool touched = Display::Tft->getTouch(&Display::TouchX, &Display::TouchY, 600);
  if (!touched)
  {
    aData->state = LV_INDEV_STATE_REL;
  }
  else
  {
    aData->state = LV_INDEV_STATE_PR;

    // set location
    aData->point.x = Display::TouchX;
    aData->point.y = Display::TouchY;

#ifdef LOG_LOOP_DEBUG
    GetLog()->printf("DI(%d):RT Id=%d X=%d, Y=%d", _id, Display::TouchX, Display::TouchY);
#endif
  }  
}


//************** Class Display ***********************************************************

TFT_eSPI* Display::Tft = NULL;
uint16_t Display::TouchX = 0;
uint16_t Display::TouchY = 0;


Display::Display(EDisplayType aDisplayType) : RemoteControl(rtDisplay)
{
  switch (aDisplayType)
  {
  case ttILI9341_24in:
    _screenWidth = 320;
    _screenHeight = 240;
    _colorDepth = 16;
    _calData[0] = 476;
    _calData[1] = 3469;
    _calData[2] = 326;
    _calData[3] = 3555;
    _calData[4] = 3;
    break;
  case ttILI9341_28in:
    _screenWidth = 320;
    _screenHeight = 240;
    _colorDepth = 16;
    _calData[0] = 412;
    _calData[1] = 3388;
    _calData[2] = 380;
    _calData[3] = 3303;
    _calData[4] = 3;
    break;
  case ttILI9341_35in:
    _screenWidth = 480;
    _screenHeight = 320;
    _colorDepth = 16;
    _calData[0] = 192;
    _calData[1] = 3590;
    _calData[2] = 335;
    _calData[3] = 3362;
    _calData[4] = 1;
    break;
  }
}

bool Display::DoSendMessage(const char* aMessage)
{
  return false;
}

void Display::Setup()
{
#ifdef LOG_SETUP
  GetLog()->printf("DI:S start");
#endif

  //Display Prepare
  Tft = new TFT_eSPI(); 
  Tft->begin();
  Tft->setRotation(1);
  Tft->setTouch(_calData);
  Tft->fillScreen(TFT_BLACK);
  delay(100);

  //LVGL init
  _buffer1 = new lv_color_t[_screenWidth * _screenHeight / 10];
  _drawBuffer = new lv_disp_draw_buf_t();

  lv_init();

  lv_disp_draw_buf_init(_drawBuffer, _buffer1, NULL, _screenWidth * _screenHeight / 10);

  // Initialize the display
  _displayDrviver = new lv_disp_drv_t();
  lv_disp_drv_init(_displayDrviver);
  // Change the following line to your display resolution 
  _displayDrviver->hor_res = _screenWidth;
  _displayDrviver->ver_res = _screenHeight;
  _displayDrviver->flush_cb = DisplayFlash;
  _displayDrviver->draw_buf = _drawBuffer;
  lv_disp_drv_register(_displayDrviver);

  // Initialize the (dummy) input device driver 
  _indevDriver = new lv_indev_drv_t();
  lv_indev_drv_init(_indevDriver);
  _indevDriver->type = LV_INDEV_TYPE_POINTER;
  _indevDriver->read_cb = ReadTouchpad;
  lv_indev_drv_register(_indevDriver);

  Tft->fillScreen(TFT_BLACK);

#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("DI:S end");
#endif
}


void Display::Loop()
{
  lv_timer_handler();
}

#endif