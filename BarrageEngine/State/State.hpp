/* ======================================================================== */
/*!
 * \file            State.hpp
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

////////////////////////////////////////////////////////////////////////////////
#ifndef State_BARRAGE_H
#define State_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  typedef void (*StateFunc)(void);
  
  //! Base application state class. 
  class State
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Constructor for State object. A state consists of up to
          three basic functions:

        \param enter
          The enter function is called once when the state is
          entered. It is optional and may be set to nullptr.

        \param update
          The update function is called once per frame. This function
          must be provided.

        \param exit
          The exit function is called once when the state is
          exited. It is optional and may be set to nullptr.
      */
      /**************************************************************/
      State(StateFunc enter, StateFunc update, StateFunc exit);

      virtual ~State() = default;

      /**************************************************************/
      /*!
        \brief
          Evaluates whether two states are equal. Two states
          are equal if they have exactly the same enter, update, and
          exit functions.

        \param rhs
          The state on the right side of the operator.

        \return
          Returns true if the states are equal and false otherwise.
      */
      /**************************************************************/
      bool operator==(const State& rhs) const;

      /**************************************************************/
      /*!
        \brief
          Evaluates whether two states are not equal. Two states
          are equal if they have exactly the same enter, update, and
          exit functions.

        \param rhs
          The state on the right side of the operator.

        \return
          Returns true if the states aren't equal and false 
          otherwise.
      */
      /**************************************************************/
      bool operator!=(const State& rhs) const;

    private:
      StateFunc enter_;  //!< Pointer to enter function for the state
      StateFunc update_; //!< Pointer to update function for the state
      StateFunc exit_;   //!< Pointer to exit function for the state

    friend class StateManager;
    friend class Engine;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // State_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////