/* ======================================================================== */
/*!
 * \file            StateManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages the current application state.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef StateManager_BARRAGE_H
#define StateManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "State.hpp"

namespace Barrage
{
  //! Manages the current application state.
  class StateManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor. Sets "current" and "next" states
          to empty.
      */
      /**************************************************************/
      StateManager();
      
      /**************************************************************/
      /*!
        \brief
          Sets the next state of the application.

          State changes at the beginning of the manager's next update 
          loop.

          This function initializes the manager if no state is
          currently running.

          If this function is called with a state that's already
          running, that state will restart.

        \param state
          The custom state to change to.
      */
      /**************************************************************/
      void SetState(State state);

      /**************************************************************/
      /*!
        \brief
          Should be called whenever the application needs to be updated.
          Does not use dt as a parameter; size of time step is fixed.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          If a state is running, exits it and removes it from the 
          state manager.
      */
      /**************************************************************/
      void QuitState();
      
      /**************************************************************/
      /*!
        \brief
          To be called by the engine. 
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Evaluates whether a state is currently running.

        \return
          Returns true if a state is running and returns false
          otherwise.
      */
      /**************************************************************/
      bool StateIsRunning();

    private:
      /**************************************************************/
      /*!
        \brief
          Evaluates whether a state change has been queued.

        \return
          Returns true if state is changing and returns false
          otherwise.
      */
      /**************************************************************/
      bool StateIsChanging() const;

      /**************************************************************/
      /*!
        \brief
          Evaluates whether a state restart has been queued.

        \return
          Returns true if state is restarting and returns false 
          otherwise.
      */
      /**************************************************************/
      bool StateIsRestarting() const;
    
    private:
      State current_;   //!< The currently running state.
      State next_;      //!< The next state to run.

      bool stateIsRunning_; //!< Keeps track of whether a state is currently running
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // StateManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////