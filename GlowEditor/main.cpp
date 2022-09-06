/* ======================================================================== */
/*!
 * \file            main.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Entry point for the demo game.
 */
 /* ======================================================================== */

#include "Editor/Editor.hpp"

int main(void)
{
  Glow::Editor* editor = new Glow::Editor;

  editor->Run();

  delete editor;

  return 0;
}

