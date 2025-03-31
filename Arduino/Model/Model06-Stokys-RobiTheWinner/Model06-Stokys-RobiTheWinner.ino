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
#define LOG_LOOP

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
#define DEFAULT_BALLLIFT_SPEED 95
#define DEFAULT_BALLOUTPUT_SPEED 100

#define BALLLIFT_MOTOR_PIN 25
#define ENDPOSITION_LIMITSWITCH_PIN 35

#define ROBIS_TIME_OF_THINK 3000 // [ms] - Prefent 4 balls together = to easy to find out the strategie

enum EGameState {
  gsPlayerSelect = 0,
  gsPlayerBall = 1,
  gsRobiThinking = 2,
  gsRobiSelect = 3,
  gsRobiBall = 4,
  gsRoundEnd = 5,
  gsGameEnd = 6,
  gsFinished = 7
};

int32_t TotalAmountOfBalls = DEFAULT_BALLS;
int32_t RestBallInGame = DEFAULT_BALLS;
EGameState PlayerMode = gsPlayerSelect;
int RobiAmountOfBall = 0;
unsigned long RobiThinkEnd = 0;

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
  GetLog()->printf("Robi the Winner");
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
  RecalcStateMachine();

  delay(5);
}

//*****************************************************************
void RecalcStateMachine() {
#ifdef LOG_LOOP_DEBUG
  GetLog()->printf("SM Mode=%d", PlayerMode);
#endif

  switch (PlayerMode) {
    case gsPlayerSelect:
      // Event driven when player select button 1, 2 or 3.
      break;
    case gsPlayerBall:
      // Do nothing, wait until event handler detect ball move end and forward state.
      break;
    case gsRobiThinking:    
      lv_obj_clear_flag(ui_LabelRobiUeberlegt, LV_OBJ_FLAG_HIDDEN);

      if (millis() > RobiThinkEnd)
      {
        PlayerMode = gsRobiSelect;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsRobiSelect");
#endif
      }
      break;
    case gsRobiSelect:
      if (RobiAmountOfBall > 0) {       
        // Players ball are down, not it's Robis choice
       lv_obj_add_flag(ui_LabelRobiUeberlegt, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text_fmt(ui_LabelRobiBallAmount, "%d", RobiAmountOfBall);
        lv_obj_clear_flag(ui_LabelRobiSpielt, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_LabelRobiBallAmount, LV_OBJ_FLAG_HIDDEN);

        RestBallInGame -= RobiAmountOfBall;
        lv_label_set_text_fmt(ui_LabelRemainingInGame, "%d", RestBallInGame);  // Show rest amount of ball

        ballsToPlay.SetValue(RobiAmountOfBall);
        ballOutputSwitch.SetValue(RemoteValue::Pos1);

        PlayerMode = gsRobiBall;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsRobiBall");
#endif
      } else {
        // Nothing to do for Robi
        PlayerMode = gsRoundEnd;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsRoundEnd");
#endif
      }
      break;
    case gsRobiBall:
      // Do nothing, wait until event handler detect ball move end and forward state.
      break;
    case gsRoundEnd:
      GetLog()->printf("SM Mode=gsRoundEnd Ball=%d", RestBallInGame);
      lv_obj_add_flag(ui_LabelRobiSpielt, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_LabelRobiBallAmount, LV_OBJ_FLAG_HIDDEN);

      if (RestBallInGame > 3) {
        // Standard round
        lv_obj_clear_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ui_ButtonOneBall, LV_STATE_DISABLED);

        lv_obj_clear_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ui_ButtonTwoBall, LV_STATE_DISABLED);

        lv_obj_clear_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ui_ButtonThreeBall, LV_STATE_DISABLED);

        PlayerMode = gsPlayerSelect;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsPlayerSelect");
#endif
      } else if (RestBallInGame > 0) {
        // Final round
        lv_obj_clear_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ui_ButtonOneBall, LV_STATE_DISABLED);

        if (RestBallInGame < 3) {
          // Disable button Select 2
          lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_ButtonThreeBall, LV_STATE_DISABLED);
        }

        PlayerMode = gsPlayerSelect;
        if (RestBallInGame < 2) {
          // Disable button Select 2
          lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
          lv_obj_add_flag(ui_ButtonTwoBall, LV_STATE_DISABLED);
        }

#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsPlayerSelect");
#endif
      } else {
        // Finished
        PlayerMode = gsGameEnd;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsGameEnd");
#endif
      }
      break;
    case gsGameEnd:
      lv_obj_clear_flag(ui_ButtonGameEnd, LV_OBJ_FLAG_HIDDEN);

      lv_obj_add_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_state(ui_ButtonOneBall, LV_STATE_DISABLED);

      lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_state(ui_ButtonTwoBall, LV_STATE_DISABLED);

      lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_state(ui_ButtonThreeBall, LV_STATE_DISABLED);
      PlayerMode = gsFinished;
#ifdef LOG_LOOP
      GetLog()->println("SM Mode=gsFinished");
#endif
    case gsFinished:
      // Ended nothing to do, press "Game lose" button to change dialog.
      break;
  }
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
    // After ball move, change to next state
#ifdef LOG_LOOP
    GetLog()->printf("EvRel: Mode=%d", PlayerMode);
#endif
    switch (PlayerMode) {
      case gsPlayerBall:
        PlayerMode = gsRobiThinking;
        if (RestBallInGame>0)
        {
        RobiThinkEnd = millis() + ROBIS_TIME_OF_THINK;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsRobiThinking");
#endif
        // Prevent total  amount onof 4  the display.
        lv_obj_add_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);

        }
        else
        {
         PlayerMode = gsRoundEnd; 
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsFinished");
#endif
        }
        break;
      case gsRobiBall:
        PlayerMode = gsRoundEnd;
#ifdef LOG_LOOP
        GetLog()->println("SM Mode=gsRoundEnd");
#endif
        break;
      default:
#ifdef LOG_LOOP
        GetLog()->printf("Player: Ignore Mode");
#endif
        break;
    }
  }
}

//*****************************************************************
// ui_events.c
//*****************************************************************
void PlayerSelect(int aPlayerAmountOfBall) {
  RestBallInGame -= aPlayerAmountOfBall;
  RobiAmountOfBall = 4 - aPlayerAmountOfBall;
  lv_label_set_text_fmt(ui_LabelRemainingInGame, "%d", RestBallInGame);
  PlayerMode = gsPlayerBall;
#ifdef LOG_LOOP
  GetLog()->println("SM Mode=gsPlayerBall");
#endif

#ifdef LOG_LOOP
  GetLog()->printf("Player: Mode=%d, Slct=%d, Robi=%d, Rest=%d", PlayerMode, aPlayerAmountOfBall, RobiAmountOfBall, RestBallInGame);
#endif

  ballsToPlay.SetValue(aPlayerAmountOfBall);
  ballOutputSwitch.SetValue(RemoteValue::Pos1);
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
  PlayerMode = gsPlayerSelect;
#ifdef LOG_LOOP
  GetLog()->println("SM Mode=gsPlayerBall");
#endif

  lv_label_set_text_fmt(ui_LabelRemainingInGame, "%d", RestBallInGame);

  // screen has still last settings, enable/disable and show/hide buttons and labels.

  // At begin Robis choice is hidden.
  lv_obj_add_flag(ui_ButtonGameEnd, LV_OBJ_FLAG_HIDDEN);

  lv_obj_add_flag(ui_LabelRobiUeberlegt, LV_OBJ_FLAG_HIDDEN);

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

  PlayerSelect(1);
}

//*****************************************************************
void ButtonTakeTwoClicked(lv_event_t* e) {
  // Hide not seleted button
  lv_obj_add_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonThreeBall, LV_OBJ_FLAG_HIDDEN);
  PlayerSelect(2);
}

//*****************************************************************
void ButtonTakeThreeClicked(lv_event_t* e) {
  // Hide not seleted button
  lv_obj_add_flag(ui_ButtonOneBall, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonTwoBall, LV_OBJ_FLAG_HIDDEN);

  PlayerSelect(3);
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
