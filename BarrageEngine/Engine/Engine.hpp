/* ======================================================================== */
/*!
 * \file            Engine.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The core engine class for a Barrage bullet hell game. Running this runs 
   the game.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_BARRAGE_H
#define Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Input/InputManager.hpp"
#include "State/StateManager.hpp"
#include "GUI/GUIManager.hpp"
#include "HTTP/HTTPManager.hpp"
#include "Objects/ObjectManager.hpp"
#include "Renderer/Renderer.hpp"
#include "Random/Random.hpp"

#include <chrono>

namespace Barrage
{   
  typedef std::chrono::steady_clock::time_point Time;
  
  //! The core engine class for a Barrage bullet hell game
  class Engine
	{
    public:   
      static Engine* Instance;

      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      Engine();

      /**************************************************************/
      /*!
        \brief
          Initializes the engine and all its subsystems.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Shuts down the engine and all its subsystems.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Should be called once when a frame begins.
      */
      /**************************************************************/
      void StartFrame();

      /**************************************************************/
      /*!
        \brief
          Should be called once when a frame ends.
      */
      /**************************************************************/
      void EndFrame();

      /**************************************************************/
      /*!
        \brief
          Gets the number of milliseconds elapsed last frame.

        \return
          Returns the number of milliseconds elapsed last frame.
      */
      /**************************************************************/
      long long DT();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's GUI manager.

        \return
          Returns a reference to the engine's GUI manager.
      */
      /**************************************************************/
      GUIManager& GUI();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's HTTP manager.

        \return
          Returns a reference to the engine's HTTP manager.
      */
      /**************************************************************/
      HTTPManager& HTTP();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      InputManager& Input();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      ObjectManager& Objects();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's random number generator.

        \return
          Returns a reference to the engine's random number generator.
      */
      /**************************************************************/
      Random& RNG();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's renderer.

        \return
          Returns a reference to the engine's renderer.
      */
      /**************************************************************/
      Renderer& Render();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's state manager.

        \return
          Returns a reference to the engine's state manager.
      */
      /**************************************************************/
      StateManager& State();

    private:
      GUIManager guiManager_;       //!< GUI manager
      HTTPManager httpManager_;     //!< HTTP manager
      InputManager inputManager_;   //!< Input manager
      ObjectManager objectManager_; //!< Object manager
      Random rng_;                  //!< Random number generator
      Renderer renderer_;           //!< Renderer
      StateManager stateManager_;   //!< State manager\

      Time frameStart_;             //!< Start time of the frame
      Time frameEnd_;               //!< End time of the frame
      long long dt_;                //!< Number of milliseconds elapsed last frame
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////