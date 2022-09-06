/* ======================================================================== */
/*!
 * \file            StateManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages the current application state.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "StateManager.hpp"

namespace Barrage
{
  StateManager::StateManager() :
    current_(nullptr, nullptr, nullptr),
    next_(nullptr, nullptr, nullptr),
    stateIsRunning_(false)
  {
  }

  void StateManager::SetState(State state)
  {
    // make sure new state at least has an update function
    if (state.update_)
    {
      // if the new state is different from the old state, queue it as the next state
      if (state != current_)
      {
        next_ = state;
      }
      // if the new state is the same as the old state, queue a state restart event
      else
      {
        // if the "next" state's update function is nullptr, it's
        // interpreted as a state restart event
        next_.update_ = nullptr;
      }

      stateIsRunning_ = true;
    }
  }

  void StateManager::Update()
  {
    // if a state change or restart event is queued...
    if (StateIsChanging())
    {
      // if it's a restart event...
      if (StateIsRestarting())
      {
        // clear the restart event
        next_ = current_;

        // call the restarting state's exit function (if it exists)
        if (current_.exit_)
          current_.exit_();

        // call the restarting state's enter function (if it exists)
        if (current_.enter_)
          current_.enter_();
      }
      // if it's a state change event...
      else
      {
        // call the exit function of the state we're leaving (if it exists)
        if (current_.exit_)
          current_.exit_();

        // move to the next state
        current_ = next_;

        // call the enter function of the state we're entering (if it exists)
        if (current_.enter_)
          current_.enter_();
      }
    }
    
    // if a state is running, call its update function no matter what
    if (current_.update_)
      current_.update_();

    // if a quit command was received, shut the current state down and clear the manager
    if (!stateIsRunning_)
    {
      if (current_.exit_)
        current_.exit_();

      current_ = State(nullptr, nullptr, nullptr);
      next_ = State(nullptr, nullptr, nullptr);
    }
  }

  void StateManager::QuitState()
  {
    stateIsRunning_ = false;
  }

  void StateManager::Shutdown()
  {
    if (current_.exit_)
      current_.exit_();

    current_ = State(nullptr, nullptr, nullptr);
    next_ = State(nullptr, nullptr, nullptr);
  }

  bool StateManager::StateIsRunning()
  {
    return stateIsRunning_;
  }

  bool StateManager::StateIsChanging() const
  {
    return current_ != next_;
  }

  bool StateManager::StateIsRestarting() const
  {
    // if the "next" state's update function is nullptr, it's
    // interpreted as a state restart event
    return next_.update_ == nullptr;
  }
}