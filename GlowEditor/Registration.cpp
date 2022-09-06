/* ======================================================================== */
/*!
 * \file            GameRegistration.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   All games must define the functions below. These functions register all
   custom code for a game.

   Any number of these functions may be empty. If any function is empty, only
   the engine's defaults will be used.
 */
/* ======================================================================== */

#include <Objects/ObjectManager.hpp>

#include "Archetypes/ShapeArchetypes.hpp"

namespace Barrage
{
  void ObjectManager::RegisterCustomComponents()
  {

  }

  void ObjectManager::RegisterCustomSystems()
  {
    
  }

  void ObjectManager::RegisterCustomSpawnFuncs()
  {

  }

  void ObjectManager::SetSystemUpdateOrder()
  {
    
  }

  void ObjectManager::CreateArchetypes()
  {
    Glow::CreateTriangleArchetypes();
    Glow::CreateControllerArchetype();
  }
}