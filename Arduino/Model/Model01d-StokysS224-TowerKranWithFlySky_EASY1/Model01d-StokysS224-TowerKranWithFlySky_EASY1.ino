//*****************************************************************
//* Model01 - Stokys S224 / Option d). Tower crane with FlySky RC (EASY Model 01)
//*
//* Stokys tower crane S224:
//* Winch by and rotation by motor N20.
//* Parts to build the model are available at www.stokys.ch
//*
//* Video of the model: https://www.youtube.com/watch?v=jrZIEZWW-Eo
//*
//* Hardware:
//* - Winch DC motor N20, max 60 1/min
//* - Rotation DC motor N20, max 60 1/min
//* - Adafruit Motorshield V2 (I2C), (Aliexpress: search I2C TB6612)
//* - FlySky FS-I6X sender
//* - FlySky FS-iA6B receiver
//*
//*****************************************************************
//* Sketch made Easy for Arduino - Arduino quick and easy
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

#include <Easy.h>


void setup() {
  //((*** Initialize: Configure your sketch here....
  FlySky* remoteControl = new FlySky(scHard);

  MotorI2C* turnMotor = new MotorI2C(3);
  Relation1to1* relationMotor = new Relation1to1(NULL, turnMotor, remoteControl->getControl(rcJoystick1X));

  MotorI2C* winchMotor = new MotorI2C(4);
  Relation1to1* relationServo = new Relation1to1(NULL, winchMotor, remoteControl->getControl(rcJoystick1Y));

  // Tipp - Motor turns in the wrong direction? Switch cables on motor shield or enclose an Inverter around the input:
  //Relation1to1* relationServo = new Relation1to1(NULL, winchMotor, new Inverter(remoteControl->getControl(rcJoystick1Y)));
  // ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required
  ControlManagerFactory::GetControlManager()->Loop();

  // Depending on Arduino it needs a short delay. Do not add any other delays!
  delay(5);
}
