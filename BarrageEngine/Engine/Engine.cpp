/* ======================================================================== */
/*!
 * \file            Engine.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The core engine class for a Barrage bullet hell game. Running this runs 
   the game.
 */
/* ======================================================================== */

#include "stdafx.h"
#include "Engine.hpp"

namespace Barrage
{
  Engine* Engine::Instance = nullptr;

  Engine::Engine() :
    guiManager_(),
    httpManager_(),
    inputManager_(),
    objectManager_(),
    rng_(),
    renderer_(),
    stateManager_(),

    frameStart_(),
    frameEnd_(),
    dt_(0)
  {
  }

  void Engine::Initialize()
  {
    Instance = this;

    renderer_.Initialize();
    inputManager_.Initialize(renderer_.GetWindowHandle());
    objectManager_.Initialize();
    guiManager_.Initialize(renderer_.GetWindowHandle());
    httpManager_.Initialize();
  }

  void Engine::Shutdown()
  {
    stateManager_.Shutdown();
    httpManager_.Shutdown();
    guiManager_.Shutdown();
    inputManager_.Shutdown();
    renderer_.Shutdown();

    Instance = nullptr;
  }

  void Engine::StartFrame()
  {
    frameStart_ = std::chrono::high_resolution_clock::now();
  }

  void Engine::EndFrame()
  {
    frameEnd_ = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd_ - frameStart_);

    dt_ = duration.count();
  }

  long long Engine::DT()
  {
    return dt_;
  }

  GUIManager& Engine::GUI()
  {
    return guiManager_;
  }

  HTTPManager& Engine::HTTP()
  {
    return httpManager_;
  }

  InputManager& Engine::Input()
  {
    return inputManager_;
  }

  ObjectManager& Engine::Objects()
  {
    return objectManager_;
  }

  Random& Engine::RNG()
  {
    return rng_;
  }

  Renderer& Engine::Render()
  {
    return renderer_;
  }

  StateManager& Engine::State()
  {
    return stateManager_;
  }
}