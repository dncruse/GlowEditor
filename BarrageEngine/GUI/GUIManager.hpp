/* ======================================================================== */
/*!
 * \file            GUIManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   ImGui wrapper class.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GUIManager_BARRAGE_H
#define GUIManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Barrage
{
	//! ImGui wrapper class
  class GUIManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      GUIManager();

      /**************************************************************/
      /*!
        \brief
          Creates ImGui context and initializes it.

        \param window
          Handle to the window ImGui will use as its render target.
      */
      /**************************************************************/
      void Initialize(GLFWwindow* window);

      /**************************************************************/
      /*!
        \brief
          Starts a new frame for widget recording. Should be called
          once per editor update, before any widget functions are
          called.
      */
      /**************************************************************/
      void StartWidgets();

      /**************************************************************/
      /*!
        \brief
          Ends the current frame for widget recording. Should be 
          called once per editor update, after all widget functions
          have been called.
      */
      /**************************************************************/
      void EndWidgets();

      /**************************************************************/
      /*!
        \brief
          Renders all widgets recorded during the previous frame.
      */
      /**************************************************************/
      void DrawWidgets();

      /**************************************************************/
      /*!
        \brief
          Shuts down and destroys the ImGui context.
      */
      /**************************************************************/
      void Shutdown();
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GUIManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////