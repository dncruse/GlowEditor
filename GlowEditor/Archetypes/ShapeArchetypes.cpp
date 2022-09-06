/* ======================================================================== */
/*!
 * \file            ShapeArchetypes.cpp
 * \par             Glow Editor
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com
 * \brief
   Archetype information for Nanoleaf shape objects.
 */
 /* ======================================================================== */

#include "ShapeArchetypes.hpp"

#include <Engine/Engine.hpp>
#include <Objects/Components/EngineComponents.hpp>

using namespace Barrage;

namespace Glow
{
  void CreateTriangleArchetypes()
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Shape");
    pool_archetype->tags_.push_back("Triangle");

    Sprite* sprite = new Sprite;
    sprite->layer_ = 0;
    sprite->texture_ = "triangle";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    pool_archetype->componentArrayNames_.push_back("PositionArray");
    pool_archetype->componentArrayNames_.push_back("RotationArray");
    pool_archetype->componentArrayNames_.push_back("ScaleArray");
    
    Engine::Instance->Objects().AddPoolArchetype("Triangle Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 640.0f;
    position_array->data_->y_ = 120.0f;
    object_archetype->components_["PositionArray"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    rotation_array->data_->angle_ = 0.0f;
    object_archetype->components_["RotationArray"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 100.0f;
    scale_array->data_->h_ = 100.0f;
    object_archetype->components_["ScaleArray"] = scale_array;

    Engine::Instance->Objects().AddObjectArchetype("Triangle Object Archetype", object_archetype);
  }

  void CreateControllerArchetype()
  {
    PoolArchetype* pool_archetype = new PoolArchetype;

    pool_archetype->tags_.push_back("Shape");
    pool_archetype->tags_.push_back("Controller");

    Sprite* sprite = new Sprite;
    sprite->layer_ = 0;
    sprite->texture_ = "controller";
    pool_archetype->sharedComponents_["Sprite"] = sprite;

    pool_archetype->componentArrayNames_.push_back("PositionArray");
    pool_archetype->componentArrayNames_.push_back("RotationArray");
    pool_archetype->componentArrayNames_.push_back("ScaleArray");

    Engine::Instance->Objects().AddPoolArchetype("Controller Pool Archetype", pool_archetype);

    ObjectArchetype* object_archetype = new ObjectArchetype;

    PositionArray* position_array = new PositionArray;
    position_array->Allocate(1);
    position_array->data_->x_ = 640.0f;
    position_array->data_->y_ = 120.0f;
    object_archetype->components_["PositionArray"] = position_array;

    RotationArray* rotation_array = new RotationArray;
    rotation_array->Allocate(1);
    rotation_array->data_->angle_ = 0.0f;
    object_archetype->components_["RotationArray"] = rotation_array;

    ScaleArray* scale_array = new ScaleArray;
    scale_array->Allocate(1);
    scale_array->data_->w_ = 100.0f;
    scale_array->data_->h_ = 100.0f;
    object_archetype->components_["ScaleArray"] = scale_array;

    Engine::Instance->Objects().AddObjectArchetype("Controller Object Archetype", object_archetype);
  }
}