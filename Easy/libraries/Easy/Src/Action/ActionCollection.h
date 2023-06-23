//*****************************************************************
//* Class ActionCollection - Header
//*
//*  Helper class when a relation should act multiple actions.
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

#ifndef EASY_ACTIONCOLLECTION_H
#define EASY_ACTIONCOLLECTION_H

#include "..\Common\BuildDefinition.h" // has to be the first 
#include "..\Common\Log.h"
#include "..\Kernel\Action.h"
#include "..\Common\ActionCollectionItem.h"
#include <LinkedList.h>

class ActionCollection : public Action {
private:
  LinkedList<ActionCollectionItem*>* _actions;

public:
  //*************************************
  ActionCollection(LinkedList<ActionCollectionItem*>* aActions)
    : Action(CreateElementId(EbtAction, EkaHelper, ACTIONCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=%d", _id, aActions->size());
#endif

    _actions = new LinkedList<ActionCollectionItem*>();

    for (int i = 0; i < aActions->size(); ++i) {
      ActionCollectionItem* action = aActions->get(i);
      _actions->add(action);
    }
  }

  //*************************************
  ActionCollection(Action* aAction1, Input* aActionParameter1, Action* aAction2, Input* aActionParameter2)
    : Action(CreateElementId(EbtAction, EkaHelper, ACTIONCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=2", _id);
#endif

    _actions = new LinkedList<ActionCollectionItem*>();
    _actions->add(new ActionCollectionItem(aAction1, aActionParameter1));
    _actions->add(new ActionCollectionItem(aAction2, aActionParameter2));
  }

  //*************************************
  ActionCollection(Action* aAction1, Input* aActionParameter1, Action* aAction2, Input* aActionParameter2, Action* aAction3, Input* aActionParameter3)
    : Action(CreateElementId(EbtAction, EkaHelper, ACTIONCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=3", _id);
#endif

    _actions = new LinkedList<ActionCollectionItem*>();
    _actions->add(new ActionCollectionItem(aAction1, aActionParameter1));
    _actions->add(new ActionCollectionItem(aAction2, aActionParameter2));
    _actions->add(new ActionCollectionItem(aAction3, aActionParameter3));
  }

  //*************************************
  ActionCollection(Action* aAction1, Input* aActionParameter1, Action* aAction2, Input* aActionParameter2, Action* aAction3, Input* aActionParameter3, Action* aAction4, Input* aActionParameter4)
    : Action(CreateElementId(EbtAction, EkaHelper, ACTIONCOLLECTION_INDEX)) {
#ifdef LOG_SETUP
    GetLog()->printf("AC(%d):C n=4", _id);
#endif
    _actions = new LinkedList<ActionCollectionItem*>();
    _actions->add(new ActionCollectionItem(aAction1, aActionParameter1));
    _actions->add(new ActionCollectionItem(aAction2, aActionParameter2));
    _actions->add(new ActionCollectionItem(aAction3, aActionParameter3));
    _actions->add(new ActionCollectionItem(aAction4, aActionParameter4));
  }

  //*************************************
  void Setup() {
    for (int i = 0; i < _actions->size(); ++i) {
      ActionCollectionItem* action = _actions->get(i);
      action->Setup();
    }
  }

  //*************************************
  void Loop() {
    for (int i = 0; i < _actions->size(); ++i) {
      ActionCollectionItem* action = _actions->get(i);
      action->Loop();
    }
  }

  //*************************************
  void Act(Input* aInput) {
    for (int i = 0; i < _actions->size(); ++i) {
      ActionCollectionItem* action = _actions->get(i);
      action->Act();
    }
  }
};

#endif
