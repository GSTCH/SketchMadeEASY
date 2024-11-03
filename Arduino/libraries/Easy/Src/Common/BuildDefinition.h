//*****************************************************************
//* Class BuildDefinition - Header
//*
//* Project is configurable by some defines, contained in this file.
//*
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

#ifndef EasyBuildDefinition_h
#define EasyBuildDefinition_h

/*
 * Log, used for test. By default it write nothing and can activated 
 * by uncomment the following lines.
 *
 * LOG : Activate Log, activate necessary code. To save memory, use log only during test.
 *
 * LOG_LOOP       : Common information during operation as value changes, ...
 * LOG_LOOP_DEBUG : Extended informations during operation, used to find bugs
 * LOG_SETUP      : Common information during startup
 * LOG_SETUP_DEBUG: Extended informations during startup, used to find bugs
 * EASY_LOG_FLUSHEACHTIME : Flush the Log after each line. Make sure to see all log but slowdown execution.
 */  

#ifndef LOG
#define LOG 
#endif

#ifndef LOG_LOOP
#define LOG_LOOP
#endif

#ifndef LOG_LOOP_DEBUG
//#define LOG_LOOP_DEBUG
#endif

#ifndef LOG_SETUP
//#define LOG_SETUP
#endif

#ifndef LOG_SETUP_DEBUG
//#define LOG_SETUP_DEBUG
#endif

#ifndef EASY_LOG_FLUSHEACHTIME
//#define EASY_LOG_FLUSHEACHTIME
#endif

/*
 * Shows Encder Motor Encoder into the SerialPlloer
 */
#ifndef PLOT_ENCODERMOTOR
//#define PLOT_ENCODERMOTOR
#endif

/*
 * Shows Rotary Encoder into the SerialPlloer
 */
#ifndef PLOT_ROTARYENCODER
//#define PLOT_ROTARYENCODER
#endif

/*
 * Usually only one remote control is used. To save memory, only one 
 * RemoteControl is supported. However, the library can also use several 
 * RemoteControls at the same time (e.g. AppInventor and FlySky together).
 * This can be activated with the CompilerSwitch.
 *
 * Pay attention: The hardware has to support the parallel communication 
 * (e.g. Bluetooth and FlySky needs a Serial communication).
 */
#ifdef __AVR_ATmega2560__
#define MULTI_REMOTECONTROL
#endif

/*
 * ID of all elements are created automatically. Sometimes it's easier to 
 * solve problems, when the ID of each element is manually defined during 
 * create. For this existing constructors, activated when set this define.
 */
#ifndef CREATE_ID_MANUALLY
//#define CREATE_ID_MANUALLY
#endif

/*
 * UltrasonicRangefinder has two modes:
 * USE_NEWPING: Use NewPing library to measure the distance
 * - : works with digital I/O and needs no library
 */
 #ifndef USE_NEWPING
//#define USE_NEWPING
#endif

#endif
