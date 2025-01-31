//*****************************************************************
//* Test Display ILI941 with Touch to enable/disable a LED
//*
//* Activate Log into ".\Common\BuildDefintion.h"
//*  --> uncomment "#define LOG" and "#define LOG_LOOP".
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

#include "ui.h"
#include <lvgl.h>  // https://docs.lvgl.io/8.0
#define LOG
#include <Easy.h>

//*****************************************************************
#define MIN_BALLS 5
#define MAX_BALLS 45
#define MIN_BALLS_PER_MOVE 1
#define MAX_BALLS_PER_MOVE 3
#define BALLS_PER_ROUND 4
#define DEFAULT_BALLS 21

#define BALLOUTPUT_MOTOR_PIN 5
#define BALLOUTPUT_MOTOR_LIMIT_SWITCH_PIN 34
#define START_IMPULS_DURATION_MILLI 500
#define WAIT_UNTIL_ACCEPT_NEXT_INPUT_MSEC 1000
#define MAX_BALLL_SPEED 100
#define DEFAULT_BALLLIFT_SPEED 100
#define DEFAULT_BALLOUTPUT_SPEED 100

#define BALLLIFT_MOTOR_PIN 25
#define ENDPOSITION_LIMITSWITCH_PIN 35

int32_t TotalAmountOfBalls = DEFAULT_BALLS;
int32_t RestBallInGame = DEFAULT_BALLS;

RemoteMonoFlop ballOutputSwitch(START_IMPULS_DURATION_MILLI);
RemoteValue ballsToPlay(0, BALLS_PER_ROUND);
RemoteValue ballTransportSwitch(RemoteValue::Pos0, RemoteValue::Pos1);
RemoteValue ballLiftSpeed(DEFAULT_BALLLIFT_SPEED, 0, MAX_BALLL_SPEED);
RemoteValue ballOutputSpeed(DEFAULT_BALLOUTPUT_SPEED, 0, MAX_BALLL_SPEED);
FixValue stopMotorSpeed(0, 0, MAX_BALLL_SPEED);
//*****************************************************************
void setup() {
  //((*** Initialize: Configure your sketch here....
#ifdef LOG
  GetLog()->printf("Display Test");
#endif

  //* Prepare (touch) display
  Display* display = new Display(ttILI9341_24in);

  //* Configure Logic of ball eject
  Actuator* ballOutput = new VariableOutput(BALLOUTPUT_MOTOR_PIN);
  Input* ballCounter = new Switch2Position(BALLOUTPUT_MOTOR_LIMIT_SWITCH_PIN, smPullDownExternal);

  Condition* countCondition = new CompareCondition(ballCounter, OpEQ, Switch2Position::On);
  Condition* startCondition = new CompareCondition(&ballOutputSwitch, OpEQ, RemoteValue::Pos1);

  Relation* ballOutRelation = new SignalCountingRelation(startCondition, countCondition, &ballsToPlay, ballOutput, &ballOutputSpeed, &stopMotorSpeed, WAIT_UNTIL_ACCEPT_NEXT_INPUT_MSEC);
  ballOutRelation->RegisterStateChangedEvent(ChangeBallOutRelationHighStateEventHandler);

  //* Configure ball Lift
  Actuator* ballLift = new VariableOutput(BALLLIFT_MOTOR_PIN);
  Input* stopPositionBallLift = new Switch2Position(ENDPOSITION_LIMITSWITCH_PIN, smPullDownExternal);

  Condition* ballLiftRunCondition = new CompareCondition(&ballTransportSwitch, OpEQ, RemoteValue::Pos1);
  Condition* endPositionReachedCondition = new CompareCondition(stopPositionBallLift, OpEQ, Switch2Position::High);

  Relation* ballLiftRelation = new ConditionEndedRelation(ballLiftRunCondition, endPositionReachedCondition, ballLift, &ballLiftSpeed, &stopMotorSpeed);
  //... ***))

  // Initialize control
  ControlManagerFactory::GetControlManager()->Setup();

  // Call the init method of the SquarelLine Studio
  ui_init();

  // Prepare screen and init value
  lv_slider_set_value(ui_SliderBallOutputSpeed, DEFAULT_BALLOUTPUT_SPEED, LV_ANIM_OFF);
  lv_slider_set_value(ui_SliderBallLiftSpeed, DEFAULT_BALLLIFT_SPEED, LV_ANIM_OFF);
}

//*****************************************************************
void loop() {
  //*** Run: No additional code is required

#ifdef LOG_LOOP_DEBUG
  GetLog()->println("Loop");
#endif

  ControlManagerFactory::GetControlManager()->Loop();

  delay(5);
}

//*****************************************************************
void ChangeBallOutRelationHighStateEventHandler(bool aState) {
#ifdef LOG_LOOP
  GetLog()->printf("EvRel: State=%d, Rest=%d", aState, RestBallInGame);
#endif

  if (aState) {
    // Disable buttons during ball transport
    lv_obj_add_state(ui_ButtonOneBall, LV_STATE_DISABLED);
    lv_obj_add_state(ui_ButtonTwoBall, LV_STATE_DISABLED);
    lv_obj_add_state(ui_ButtonThreeBall, LV_STATE_DISABLED);
  } else {
    // All balls transported, enable button and hide robi text+amount
    lv_obj_clear_state(ui_ButtonOneBall, LV_STATE_DISABLED);
    lv_obj_clear_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);

    if (RestBallInGame > 1) {
      lv_obj_clear_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_state(ui_ButtonTwoBall, LV_STATE_DISABLED);
    } else {
      lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_state(ui_ButtonTwoBall, LV_STATE_DISABLED);
    }

    if (RestBallInGame > 2) {
      lv_obj_clear_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_state(ui_ButtonThreeBall, LV_STATE_DISABLED);
    } else {
      lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_state(ui_ButtonThreeBall, LV_STATE_DISABLED);
    }

    lv_obj_add_flag(ui_LabelRobiSpielt, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_LabelRobiBallAmount, LV_OBJ_FLAG_HIDDEN);
  }
}

//*****************************************************************
// ui_events.c
//*****************************************************************
void PlayMove(int aPlayerAmountOfBall) {
  if (RestBallInGame > 4) {
#ifdef LOG_LOOP
    GetLog()->printf("Play: Ply=%d, Rest=%d", aPlayerAmountOfBall, RestBallInGame);
#endif

    // Play next move
    // Calculate the remaining ball amount and write it to display
    RestBallInGame -= 4;
    lv_label_set_text_fmt(ui_LabelRemainingInGame, "%d", RestBallInGame);  // 4 Balls per Round - Players choice

    // Calculate Robis move
    lv_label_set_text_fmt(ui_LabelRobiBallAmount, "%d", 4 - aPlayerAmountOfBall);  // 4 Balls per Round - Players choice
    lv_obj_clear_flag(ui_LabelRobiSpielt, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_LabelRobiBallAmount, LV_OBJ_FLAG_HIDDEN);

    // Prepare game end.
    // No missing break: Smart! Case 1: button 2+3 disabled, case 2 only button 3
    switch (RestBallInGame) {
      case 1:
        lv_obj_add_state(ui_ButtonTwoBall, LV_STATE_DISABLED);
        ballsToPlay.SetValue(RestBallInGame);
      case 2:
        lv_obj_add_state(ui_ButtonThreeBall, LV_STATE_DISABLED);
    }
  } else {
#ifdef LOG_LOOP
    GetLog()->printf("End: Ply=%d, Rest=%d", aPlayerAmountOfBall, RestBallInGame);
#endif

    // Last move
    RestBallInGame -= aPlayerAmountOfBall;

    lv_label_set_text_fmt(ui_LabelRobiBallAmount, "%d", RestBallInGame - aPlayerAmountOfBall);  // REST - Players choice
    lv_obj_clear_flag(ui_ButtonGameEnd, LV_OBJ_FLAG_HIDDEN);

    lv_label_set_text_fmt(ui_LabelRemainingInGame, "%d", RestBallInGame);
  }

#ifdef LOG_LOOP
  GetLog()->println("Play: balls");
#endif

  ballOutputSwitch.SetValue(1);
}

//*****************************************************************
void ButtonSettingsOkayClicked(lv_event_t* e) {
  int32_t value = lv_slider_get_value(ui_SliderBallAmount);
  TotalAmountOfBalls = value;
}

//*****************************************************************
void ButtonStartGameClicked(lv_event_t* e) {
#ifdef LOG_LOOP
  GetLog()->println("Start clicked");
#endif

  RestBallInGame = TotalAmountOfBalls;
  ballsToPlay.SetValue(BALLS_PER_ROUND);
  lv_label_set_text_fmt(ui_LabelRemainingInGame, "%d", RestBallInGame);

  // screen has still last settings, enable/disable and show/hide buttons and labels.

  // At begin Robis choice is hidden.
  lv_obj_add_flag(ui_ButtonGameEnd, LV_OBJ_FLAG_HIDDEN);

  lv_obj_add_flag(ui_LabelRobiSpielt, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_LabelRobiBallAmount, LV_OBJ_FLAG_HIDDEN);

  lv_obj_clear_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(ui_ButtonOneBall, LV_STATE_DISABLED);

  lv_obj_clear_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(ui_ButtonTwoBall, LV_STATE_DISABLED);

  lv_obj_clear_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(ui_ButtonThreeBall, LV_STATE_DISABLED);
}

//*****************************************************************
void ButtonTakeOneClicked(lv_event_t* e) {
  // Hide not seleted button
  lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);

  PlayMove(1);
}

//*****************************************************************
void ButtonTakeTwoClicked(lv_event_t* e) {
  // Hide not seleted button
  lv_obj_add_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
  PlayMove(2);
}

//*****************************************************************
void ButtonTakeThreeClicked(lv_event_t* e) {
  // Hide not seleted button
  lv_obj_add_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);

  PlayMove(3);
}

//*****************************************************************
void ButtonGameFinshedClick(lv_event_t* e) {
  // Your code here
}

//*****************************************************************
void ButtonOpenSettingClicked(lv_event_t* e) {
  lv_slider_set_value(ui_SliderBallAmount, TotalAmountOfBalls, LV_ANIM_OFF);
  lv_slider_set_range(ui_SliderBallAmount, MIN_BALLS, MAX_BALLS);
}

//*****************************************************************
void StopBallOutputClicked(lv_event_t* e) {
#ifdef LOG
  GetLog()->printf("BO stop");
#endif
  ballOutputSwitch.SetValue(RemoteValue::Pos0);
}

//*****************************************************************
void StartBallOutputClicked(lv_event_t* e) {
#ifdef LOG
  GetLog()->printf("BO start");
#endif
  ballsToPlay.SetValue(lv_spinbox_get_value(ui_SpinBoxTestBallAmount));
  ballOutputSwitch.SetValue(RemoteValue::Pos1);
}

//*****************************************************************
void BallLiftStartClicked(lv_event_t* e) {
#ifdef LOG
  GetLog()->printf("BL start");
#endif
  ballTransportSwitch.SetValue(RemoteValue::Pos1);
}

//*****************************************************************
void BallLiftStopClicked(lv_event_t* e) {
#ifdef LOG
  GetLog()->printf("BL stop");
#endif
  ballTransportSwitch.SetValue(RemoteValue::Pos0);
}

//*****************************************************************
void BallOutputSpeedChanged(lv_event_t* e) {
  int32_t value = lv_slider_get_value(ui_SliderBallOutputSpeed);
  ballOutputSpeed.SetValue(value);
#ifdef LOG
  GetLog()->printf("BO spd=%d", value);
#endif
}

//*****************************************************************
void BallLiftSpeedChanged(lv_event_t* e) {
  int32_t value = lv_slider_get_value(ui_SliderBallLiftSpeed);
  ballLiftSpeed.SetValue(value);
#ifdef LOG
  GetLog()->printf("BL spd=%d", value);
#endif
}
