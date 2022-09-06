/* ======================================================================== */
/*!
 * \file            GUIManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   ImGui wrapper class.
 */
/* ======================================================================== */

#include "GUIManager.hpp"

namespace Barrage
{
  GUIManager::GUIManager()
  {
  }

  void GUIManager::Initialize(GLFWwindow* window)
  {
    IMGUI_CHECKVERSION();
    if (!ImGui::CreateContext())
      return;

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
      return;

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
      return;
  }

  void GUIManager::StartWidgets()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void GUIManager::EndWidgets()
  {
    ImGui::Render();
  }

  void GUIManager::DrawWidgets()
  {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void GUIManager::Shutdown()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
  }
}