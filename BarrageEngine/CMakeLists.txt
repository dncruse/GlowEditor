# =====================================================================================================================
# MIT License
# 
# Copyright (c) 2022 Dragonscale-Games
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# =====================================================================================================================


# =====================================================================================================================
# File:         CMakeLists.txt
# Author:       David Wong Cascante
# Email:        dragonscale.games.llc@gmail.com
# Date:         1/8/2022
# =====================================================================================================================

# Sets the folder name for OS specific implementations.
if(MSVC)
  set(OS_IMPL_FOLDER "MSVC")
else()
  set(OS_IMPL_FOLDER "LINUX")
endif()

# Add the sources for the core library.
add_library(BarrageCore STATIC 
  "Engine/Engine.cpp" "Engine/Engine.hpp"

  "GUI/GUIManager.cpp" "GUI/GUIManager.hpp" 

  "HTTP/HTTPManager.cpp" "HTTP/HTTPManager.hpp"

  "Input/InputManager.cpp" "Input/InputManager.hpp" 
  "Input/KeyMap.hpp" 
  
  "Objects/Components/BaseClasses/ComponentArray.cpp" "Objects/Components/BaseClasses/ComponentArray.hpp" 
  "Objects/Components/BaseClasses/SharedComponent.cpp"   "Objects/Components/BaseClasses/SharedComponent.hpp"   
  "Objects/Components/BaseClasses/BaseComponent.hpp" 
  "Objects/ObjectManager.cpp" "Objects/ObjectManager.hpp" 
  "Objects/Pools/Pool.cpp"    "Objects/Pools/Pool.hpp"  
  
  "Objects/Systems/EngineSystems.hpp"
  "Objects/Systems/BaseSystem.cpp"                    "Objects/Systems/BaseSystem.hpp"   
  "Objects/Systems/Destruction/DestructionSystem.cpp" "Objects/Systems/Destruction/DestructionSystem.hpp"    
  "Objects/Systems/Creation/CreationSystem.cpp"       "Objects/Systems/Creation/CreationSystem.hpp"  
  "Objects/Systems/Draw/DrawSystem.cpp"               "Objects/Systems/Draw/DrawSystem.hpp" 
  
  "Objects/Components/EngineComponents.hpp"
  
  "Objects/SpawnFuncs/SpawnFuncManager.hpp"                "Objects/SpawnFuncs/SpawnFuncManager.cpp"  
  "Objects/Archetypes/ArchetypeManager.cpp"                "Objects/Archetypes/ArchetypeManager.hpp" 
  "Objects/Pools/PoolManager.cpp"                          "Objects/Pools/PoolManager.hpp" 
  "Objects/Systems/SystemManager.cpp"                      "Objects/Systems/SystemManager.hpp" 
  "Objects/Components/ComponentAllocator.cpp"              "Objects/Components/ComponentAllocator.hpp" 
  "Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp" "Objects/Archetypes/ObjectArchetype/ObjectArchetype.cpp" 
  "Objects/Archetypes/PoolArchetype/PoolArchetype.hpp"     "Objects/Archetypes/PoolArchetype/PoolArchetype.cpp" 
  "Objects/SpawnFuncs/EngineSpawnFuncs.hpp" 
  "Objects/Pools/PoolType.cpp" "Objects/Pools/PoolType.hpp" 
  "Objects/Components/ComponentArrays/DestructibleArray.hpp" 
  "Objects/Components/ComponentArrays/PositionArray.hpp" 
  "Objects/Components/ComponentArrays/ScaleArray.hpp" 
  "Objects/Components/ComponentArrays/RotationArray.hpp" 
  "Objects/Components/SharedComponents/Spawner.hpp"
  "Objects/Components/SharedComponents/Sprite.hpp"
  "Objects/Components/ComponentArrays/LifetimeArray.hpp" 
  "Objects/Components/ComponentArrays/VelocityArray.hpp" 
  "Objects/Components/SharedComponents/CircleCollider.hpp" 
  "Objects/Components/ComponentArrays/AngularSpeedArray.hpp" 

  "Objects/Systems/Movement/MovementSystem.hpp" "Objects/Systems/Movement/MovementSystem.cpp"
  "Objects/Systems/Collision/CollisionSystem.hpp" "Objects/Systems/Collision/CollisionSystem.cpp" 
  "Objects/Components/SharedComponents/RNG.hpp" 
  "Objects/SpawnFuncs/Direction/DirectionFuncs.hpp" "Objects/SpawnFuncs/Direction/DirectionFuncs.cpp"
  "Objects/SpawnFuncs/Position/PositionFuncs.hpp" "Objects/SpawnFuncs/Position/PositionFuncs.cpp"
  "Objects/Components/SharedComponents/BoundaryBox.hpp"

  "Random/Random.cpp" "Random/Random.hpp" 
  
  "Renderer/Renderer.cpp" "Renderer/Renderer.hpp" 
  "Renderer/Shader/Shader.cpp" "Renderer/Shader/Shader.hpp" 
  "Renderer/Shader/ShaderManager.cpp" "Renderer/Shader/ShaderManager.hpp" 
  "Renderer/Texture/Texture.cpp" "Renderer/Texture/Texture.hpp" 
  "Renderer/Texture/TextureManager.cpp" "Renderer/Texture/TextureManager.hpp" 

  "State/StateManager.cpp" "State/StateManager.hpp" 
  "State/State.cpp" "State/State.hpp" 

  "Utilities/Utilities.hpp"

  "template.cxx"
  "stdafx.h"
)

# And link the dependencies for this library.
# target_link_libraries(BarrageCore PUBLIC glad glfw glm rapidjson stb_image RTTR::Core)
target_link_libraries(BarrageCore LINK_PUBLIC glad glfw glm::glm rapidjson stb_image imgui curlpp)
target_include_directories(BarrageCore PUBLIC ${RTTR_DIR})
target_include_directories(BarrageCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
