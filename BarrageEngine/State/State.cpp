/* ======================================================================== */
/*!
 * \file            State.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base application state class. To create a custom state:
     1. Create a class that's derived from State.
     2. Create up to three static member functions:
        static void Enter(); (optional)
        static void Update();
        static void Exit();  (optional)
     3. Create a default constructor for the custom state class with no 
        parameters, and set the class's enter_, update_, and exit_ fields to 
        the corresponding static functions. The enter_ and exit_ fields may
        be set to nullptr.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "State.hpp"

namespace Barrage
{
  State::State(StateFunc enter, StateFunc update, StateFunc exit) :
    enter_(enter), update_(update), exit_(exit)
  {
  }

  bool State::operator==(const State& rhs) const
  {
    return (rhs.enter_ == enter_) && (rhs.update_ == update_) && (rhs.exit_ == exit_);
  }

  bool State::operator!=(const State& rhs) const
  {
    return !(*this == rhs);
  }
}