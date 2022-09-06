/* ======================================================================== */
/*!
 * \file            Editor.cpp
 * \par             Glow Editor
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Main loop for Glow Editor.
 */
/* ======================================================================== */

#include "Editor.hpp"

#include <States/State_Main.hpp>

namespace Glow
{
  Editor::Editor() :
    engine_(),
    isRunning_(false)
  {
  }

  void Editor::Run()
  {
    if (!isRunning_)
    {
      isRunning_ = true;
      
      State_Main::ReadConfigFile();

      Initialize();

      while (isRunning_)
      {
        Update();
      }

      Shutdown();

      State_Main::WriteConfigFile();

      isRunning_ = false;
    }
  }

  void Editor::Initialize()
  {
    engine_.Initialize();

    engine_.State().SetState(State_Main());
  }

  void Editor::Update()
  { 
    engine_.StartFrame();
    
    engine_.Input().Update();

    engine_.GUI().StartWidgets();
    engine_.State().Update();
    engine_.GUI().EndWidgets();

    engine_.Render().StartFrame();
    engine_.Objects().Draw();
    engine_.GUI().DrawWidgets();
    engine_.Render().EndFrame();

    if (engine_.Render().WindowClosed())
      isRunning_ = false;

    engine_.EndFrame();
  }

  void Editor::Shutdown()
  { 
    engine_.Shutdown();
  }
}