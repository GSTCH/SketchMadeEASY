//*****************************************************************
//* Class ControlManager - Implementation
//*
//* Internal class
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

#include "ControlManager.h"

//*************************************
ControlManager::ControlManager()
  : ControlManagerBase() {
  _realInputs = new LinkedList<Input*>();
  _toolInputs = new LinkedList<Input*>();
  _conditions = new LinkedList<Condition*>();
  _logicInputs = new LinkedList<Input*>();
  _relations = new LinkedList<Relation*>();
  _actions = new LinkedList<Action*>();

#ifdef MULTI_REMOTECONTROL
  _remoteControls = new LinkedList<RemoteControl*>();
#else
  _remoteControl = NULL;
#endif
}

//*************************************
void ControlManager::Setup() {
#ifdef LOG_SETUP
  GetLog()->printf("CM:S RI=%d, TI=%d, LI=%d, R=%d, A=%d", _realInputs->size(), _toolInputs->size(), _logicInputs->size(), _relations->size(), _actions->size());
#endif

#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S RI");
#endif
  for (int i = 0; i < _realInputs->size(); i++) {
    Input* input = _realInputs->get(i);
    input->Setup();
  }

#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S TI");
#endif
  for (int i = 0; i < _toolInputs->size(); i++) {
    Input* input = _toolInputs->get(i);
    input->Setup();
  }

#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S C");
#endif
  for (int i = 0; i < _conditions->size(); ++i) {
    Condition* condition = _conditions->get(i);
    condition->Setup();
  }

#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S LI");
#endif
  for (int i = 0; i < _logicInputs->size(); i++) {
    Input* input = _logicInputs->get(i);
    input->Setup();
  }

#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S R");
#endif
  for (int i = 0; i < _relations->size(); i++) {
    Relation* relation = _relations->get(i);
    relation->Setup();
  }

#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S A");
#endif
  for (int i = 0; i < _actions->size(); i++) {
    Action* action = _actions->get(i);
    action->Setup();
  }

  // The  remote control logic can wait until the connection has been made.
  // Because of this we call this as last to be sure that all has been initialized before.
#ifdef MULTI_REMOTECONTROL
#ifdef #ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S RC*");
#endif
  for (int i = 0; i < _remoteControls->size(); i++) {
    RemoteControl* remoteControl = _remoteControls->get(i);
    GetLog()->printf("CM:S RC%d", i);
    remoteControl->Setup();
  }
#else
#ifdef LOG_SETUP_DEBUG
  GetLog()->println("CM:S RC");
#endif

  if (_remoteControl != NULL) {
    _remoteControl->Setup();
#endif
  }

#ifdef LOG_SETUP
GetLog()->println("CM:S }");
#endif
}

//*************************************
void ControlManager::Loop() {
#ifdef LOG_LOOP_DEBUG
  GetLog()->println("CM::L");
#endif

  // Update it's value
  for (int i = 0; i < _realInputs->size(); ++i) {
    Input* input = _realInputs->get(i);
    input->Loop();
  }

#ifdef MULTI_REMOTECONTROL
  for (int i = 0; i < _remoteControls->size(); i++) {
    RemoteControl* remoteControl = _remoteControls->get(i);
    remoteControl->Loop();
  }
#else
  if (_remoteControl != NULL) {
     // RemoteControl update the remote inputs
    _remoteControl->Loop();
  }
#endif

  for (int i = 0; i < _toolInputs->size(); ++i) {
    Input* input = _toolInputs->get(i);
    input->Loop();
  }

  for (int i = 0; i < _conditions->size(); ++i) {
    Condition* condition = _conditions->get(i);
    condition->Loop();
  }

  for (int i = 0; i < _logicInputs->size(); ++i) {
    Input* input = _logicInputs->get(i);
    input->Loop();
  }

  for (int i = 0; i < _relations->size(); ++i) {
    Relation* relation = _relations->get(i);
    relation->Loop();
  }

  for (int i = 0; i < _actions->size(); ++i) {
    Action* action = _actions->get(i);
    action->Loop();
  }
}

//*************************************
void ControlManager::Add(Input* aInput) {
#ifdef LOG_SETUP
  GetLog()->printf("CM:+ I %d", aInput->GetId());
#endif

  if (aInput->GetBaseType() == EbtInput && aInput->GetKind() == EkiHelper) {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("CM:+ TI %d", aInput->GetId());
#endif
    _toolInputs->add(aInput);
  } else if (aInput->GetBaseType() == EbtInput && aInput->GetKind() == EkiVirtual) {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("CM:+ VI %d", aInput->GetId());
#endif
    _realInputs->add(aInput);
  } else if (aInput->GetBaseType() == EbtInput && aInput->GetKind() == EkiLogic) {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("CM:+ LI %d", aInput->GetId());
#endif
    _logicInputs->add(aInput);
  } else {
#ifdef LOG_SETUP_DEBUG
    GetLog()->printf("CM:+ RI %d", aInput->GetId());
#endif

    _realInputs->add(aInput);
  }
}

//*************************************
void ControlManager::Add(Relation* aRelation) {
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("CM:+ R %d", aRelation->GetId());
#endif
  _relations->add(aRelation);
}

//*************************************
void ControlManager::Add(Action* aAction) {
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("CM:+ A %d", aAction->GetId());
#endif
  _actions->add(aAction);
}

//*************************************
void ControlManager::Add(Condition* aCondition) {
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("CM:+ C %d", aCondition->GetId());
#endif

  _conditions->add(aCondition);
}

//*************************************
void ControlManager::Set(RemoteControl* aRemoteControl) {
#ifdef MULTI_REMOTECONTROL
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("CM:++ RC");
#endif
  _remoteControls->add(aRemoteControl);
  
#else
#ifdef LOG_SETUP_DEBUG
  GetLog()->printf("CM:+ RC");
#endif
  _remoteControl = aRemoteControl;
#endif
}

//*************************************
Element* ControlManager::Get(int aId) {
  for (int i = 0; i < _realInputs->size(); ++i) {
    Input* elementAtPos = _realInputs->get(i);
    if (elementAtPos->GetId() == aId) {
      return elementAtPos;
    }
  }

  for (int i = 0; i < _toolInputs->size(); ++i) {
    Input* elementAtPos = _toolInputs->get(i);
    if (elementAtPos->GetId() == aId) {
      return elementAtPos;
    }
  }

  for (int i = 0; i < _conditions->size(); ++i) {
    Condition* elementAtPos = _conditions->get(i);
    if (elementAtPos->GetId() == aId) {
      return elementAtPos;
    }
  }

  for (int i = 0; i < _logicInputs->size(); ++i) {
    Input* elementAtPos = _logicInputs->get(i);
    if (elementAtPos->GetId() == aId) {
      return elementAtPos;
    }
  }

  for (int i = 0; i < _relations->size(); ++i) {
    Relation* elementAtPos = _relations->get(i);
    if (elementAtPos->GetId() == aId) {
      return elementAtPos;
    }
  }

  for (int i = 0; i < _actions->size(); ++i) {
    Action* elementAtPos = _actions->get(i);
    if (elementAtPos->GetId() == aId) {
      return elementAtPos;
    }
  }

  return NULL;
}
