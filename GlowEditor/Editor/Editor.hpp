/* ======================================================================== */
/*!
 * \file            Editor.hpp
 * \par             Glow Editor
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Main loop for Glow Editor.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Editor_GLOW_H
#define Editor_GLOW_H
////////////////////////////////////////////////////////////////////////////////

#include <Engine/Engine.hpp>

namespace Glow
{
	//! Editor for Barrage Engine
  class Editor
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      Editor();

      /**************************************************************/
      /*!
        \brief
          Calling this runs the editor.
      */
      /**************************************************************/
      void Run();

    private:
      /**************************************************************/
      /*!
        \brief
          Initializes Barrage engine and editor systems.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Updates main editor loop.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          Shuts down Barrage engine and editor systems.
      */
      /**************************************************************/
      void Shutdown();

    private:
      Barrage::Engine engine_;  //!< Barrage engine instance
      bool isRunning_;          //!< keeps track of whether the editor is running
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Editor_GLOW_H
////////////////////////////////////////////////////////////////////////////////