/* ======================================================================== */
/*!
 * \file            State_Main.cpp
 * \par             Glow Editor
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com
 * \brief
   The main application state for Glow Editor.
 */
 /* ======================================================================== */

#include "State_Main.hpp"

#include <Engine/Engine.hpp>
#include <glm/gtx/color_space.hpp>
#include <iostream>
#include <climits>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <fstream>
#include <filesystem>
#include <imgui/imgui_stdlib.h>
#include <vector>

using namespace Barrage;

namespace Glow
{
  rj::Document State_Main::lightConfig_ = rj::Document();
  long long State_Main::timer_ = 0;
  glm::vec3 State_Main::color_(0.5f, 0.5f, 0.5f);
  int State_Main::colorTemperature_ = 3000;
  std::vector<std::string> State_Main::effects_ = std::vector<std::string>();
  int State_Main::orientation_ = 0;
  std::string State_Main::authToken_ = std::string();
  std::string State_Main::host_ = std::string("http://xxx.xxx.xxx.xxx:16021");

  State_Main::State_Main() : State(Enter, Update, Exit)
  {
  }

  void State_Main::ReadConfigFile()
  {
    if (!std::filesystem::exists("glowconfig.json"))
    {
      return;
    }

    std::ifstream ifs("glowconfig.json");

    if (!ifs.is_open())
    {
      return;
    }

    rj::IStreamWrapper isw(ifs);

    rj::Document config;
    config.ParseStream(isw);

    if (!config.IsObject())
    {
      return;
    }

    if (config.HasMember("authToken"))
    {
      authToken_ = config["authToken"].GetString();
    }

    if (config.HasMember("host"))
    {
      host_ = config["host"].GetString();
    }
  }

  void State_Main::WriteConfigFile()
  {
    rj::Document config;
    config.SetObject();

    config.AddMember("authToken", rj::Value().SetString(authToken_.c_str(), authToken_.length(), config.GetAllocator()), config.GetAllocator());
    config.AddMember("host", rj::Value().SetString(host_.c_str(), host_.length(), config.GetAllocator()), config.GetAllocator());

    std::ofstream ofs("glowconfig.json");

    if (!ofs.is_open())
    {
      return;
    }

    rj::OStreamWrapper osw(ofs);

    rj::PrettyWriter<rj::OStreamWrapper> writer(osw);
    config.Accept(writer);
  }

  void State_Main::Enter()
  {
    Engine::Instance->Objects().CreatePool("Triangle Pool", "Triangle Pool Archetype", 500);
    Engine::Instance->Objects().CreatePool("Controller Pool", "Controller Pool Archetype");

    GetAllPanelData();
  }

  void State_Main::Update()
  {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(430, 720), ImGuiCond_Once);

    ImGui::Begin("Editor", 0, (1 << 1) | (1 << 2) | (1 << 5) | (1 << 0));

    if (ImGui::BeginTabBar("Tab bar"))
    {
      if (ImGui::BeginTabItem("Authorization"))
      {
        ImGui::Text("");
        
        ImGui::Text("Host:");
        ImGui::PushID("hostInput");
        ImGui::InputText("", &host_);
        ImGui::PopID();
        
        ImGui::Text("");

        ImGui::Text("Token");
        ImGui::PushID("authInput");
        ImGui::InputText("", &authToken_);
        ImGui::PopID();

        ImGui::Text("");

        if (ImGui::Button("Identify panels"))
        {
          IdentifyPanels();
        }

        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("State"))
      {
        ImGui::Text("");

        ImGui::Text("Light switch");
        if (ImGui::Button("On"))
        {
          SetOnOff(true);
        }
        ImGui::SameLine();
        if (ImGui::Button("Off"))
        {
          SetOnOff(false);
        }

        ImGui::Text("");

        ImGui::Text("Orientation");
        ImGui::PushID("orientationInput");
        if (ImGui::SliderInt("", &orientation_, 0, 360))
        {
          SetOrientation();
        }
        ImGui::PopID();

        ImGui::Text("");

        ImGui::Text("Color");
        ImGui::PushID("colorInput");
        if (ImGui::ColorPicker3("", reinterpret_cast<float*>(&color_), 1 << 28 | 1 << 5))
        {
          SetColor();
        }
        ImGui::PopID();

        ImGui::Text("Hue");
        ImGui::PushID("hueInput");
        if (ImGui::SliderFloat("", &(color_.x), 0, 1.0f))
        {
          SetHue();
        }
        ImGui::PopID();

        ImGui::Text("Saturation");
        ImGui::PushID("satInput");
        if (ImGui::SliderFloat("", &(color_.y), 0, 1.0f))
        {
          SetSaturation();
        }
        ImGui::PopID();

        ImGui::Text("Brightness");
        ImGui::PushID("brightnessInput");
        if (ImGui::SliderFloat("", &(color_.z), 0, 1.0f))
        {
          SetBrightness();
        }
        ImGui::PopID();

        ImGui::Text("Color Temperature");
        ImGui::PushID("ctInput");
        if (ImGui::SliderInt("", &colorTemperature_, 1200, 6500))
        {
          SetColorTemperature();
        }
        ImGui::PopID();

        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Effects"))
      {
        ImGui::Text("");

        if (effects_.empty())
        {
          ImGui::Text("(No effects on controller)");
        }
        else {
          for (auto it = effects_.begin(); it != effects_.end(); ++it)
          {
            if (ImGui::Button((*it).c_str()))
            {
              SetEffect(*it);
            }
          }
        }

        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }

    ImGui::End();

    timer_ += Engine::Instance->DT();
  }

  void State_Main::Exit()
  {
    Engine::Instance->Objects().DeleteAllPools();
  }

  void State_Main::IdentifyPanels()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/identify";
    
    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");
    Engine::Instance->HTTP().SetRequestBody("");
    Engine::Instance->HTTP().SendRequest();
  }

  void State_Main::GetAllPanelData()
  {
    std::string url = host_ + "/api/v1/" + authToken_;
    
    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("GET");
    Engine::Instance->HTTP().SendRequest();

    const std::string& response = Engine::Instance->HTTP().GetResponse();

    lightConfig_.Parse(response.c_str());

    if (!lightConfig_.IsObject())
    {
      return;
    }

    if (lightConfig_.HasMember("state"))
    {
      const rj::Value& state = lightConfig_["state"];

      if (state.HasMember("hue"))
      {
        const rj::Value& hue = state["hue"];

        if (hue.HasMember("value") && hue["value"].IsNumber())
        {
          color_.x = hue["value"].GetFloat() / 360.0f;
        }
      }

      if (state.HasMember("sat"))
      {
        const rj::Value& sat = state["sat"];

        if (sat.HasMember("value") && sat["value"].IsNumber())
        {
          color_.y = sat["value"].GetFloat() / 100.0f;
        }
      }

      if (state.HasMember("ct"))
      {
        const rj::Value& color_temperature = state["ct"];

        if (color_temperature.HasMember("value") && color_temperature["value"].IsNumber())
        {
          colorTemperature_ = color_temperature["value"].GetInt();
        }
      }
    }

    if (lightConfig_.HasMember("effects"))
    {
      const rj::Value& effects = lightConfig_["effects"];

      if (effects.HasMember("effectsList"))
      {
        const rj::Value& effects_list = effects["effectsList"];

        if (effects_list.IsArray())
        {
          effects_.clear();
          
          for (rj::SizeType i = 0; i < effects_list.Size(); ++i)
          {
            const rj::Value& effect = effects_list[i];

            if (effect.IsString())
            {
              effects_.push_back(effect.GetString());
            }
          }
        }
      }
    }

    if (lightConfig_.HasMember("panelLayout"))
    {
      const rj::Value& panel_layout = lightConfig_["panelLayout"];

      float global_angle = 0.0f;

      if (panel_layout.HasMember("globalOrientation"))
      {
        const rj::Value& global_orientation = panel_layout["globalOrientation"];

        if (global_orientation.HasMember("value") && global_orientation["value"].IsNumber())
        {
          global_angle = 3.14159f / 180.0f * -global_orientation["value"].GetFloat();
          orientation_ = global_orientation["value"].GetInt();
        }
      }

      if (panel_layout.HasMember("layout"))
      {
        const rj::Value& layout = panel_layout["layout"];

        if (layout.HasMember("positionData"))
        {
          const rj::Value& position_data = layout["positionData"];

          if (position_data.IsArray())
          {
            Pool* triangle_pool = Engine::Instance->Objects().GetPool("Triangle Pool");
            PositionArray& triangle_positions = *(triangle_pool->GetComponentArray<PositionArray>("PositionArray"));
            RotationArray& triangle_rotations = *(triangle_pool->GetComponentArray<RotationArray>("RotationArray"));
            ScaleArray& triangle_scales = *(triangle_pool->GetComponentArray<ScaleArray>("ScaleArray"));

            Pool* controller_pool = Engine::Instance->Objects().GetPool("Controller Pool");
            PositionArray& controller_positions = *(controller_pool->GetComponentArray<PositionArray>("PositionArray"));
            RotationArray& controller_rotations = *(controller_pool->GetComponentArray<RotationArray>("RotationArray"));
            ScaleArray& controller_scales = *(controller_pool->GetComponentArray<ScaleArray>("ScaleArray"));
            
            triangle_pool->size_ = 0;
            controller_pool->size_ = 0;

            float side_length = 100.0f;

            float x_min = std::numeric_limits<float>::max();
            float x_max = std::numeric_limits<float>::lowest();
            float y_min = std::numeric_limits<float>::max();
            float y_max = std::numeric_limits<float>::lowest();

            if (layout.HasMember("sideLength") && layout["sideLength"].IsNumber())
            {
              side_length = layout["sideLength"].GetFloat() * 1.1f;
            }

            for (rj::SizeType i = 0; i < position_data.Size(); ++i)
            {
              const rj::Value& position = position_data[i];

              if (position.HasMember("shapeType") && position["shapeType"].IsNumber() 
                && position.HasMember("x") && position["x"].IsNumber() 
                && position.HasMember("y") && position["y"].IsNumber()
                && position.HasMember("o") && position["o"].IsNumber())
              {
                int shape_type = position["shapeType"].GetInt();

                if (shape_type == 8 && triangle_pool->size_ < triangle_pool->capacity_)
                {
                  unsigned index = triangle_pool->size_;

                  Engine::Instance->Objects().CreateObject("Triangle Pool", "Triangle Object Archetype");

                  float x_pos = position["x"].GetFloat();
                  float y_pos = position["y"].GetFloat();

                  triangle_positions[index].x_ = x_pos * glm::cos(global_angle) - y_pos * glm::sin(global_angle);
                  triangle_positions[index].y_ = x_pos * glm::sin(global_angle) + y_pos * glm::cos(global_angle);
                  triangle_rotations[index].angle_ = (-position["o"].GetFloat()) / 180.0f * 3.14159f + global_angle;
                  triangle_scales[index].w_ = side_length;
                  triangle_scales[index].h_ = side_length;

                  if (triangle_positions[index].x_ < x_min)
                    x_min = triangle_positions[index].x_;

                  if (triangle_positions[index].x_ > x_max)
                    x_max = triangle_positions[index].x_;

                  if (triangle_positions[index].y_ < y_min)
                    y_min = triangle_positions[index].y_;

                  if (triangle_positions[index].y_ > y_max)
                    y_max = triangle_positions[index].y_;
                }
                else if (shape_type == 12 && controller_pool->size_ < controller_pool->capacity_)
                {
                  unsigned index = controller_pool->size_;

                  Engine::Instance->Objects().CreateObject("Controller Pool", "Controller Object Archetype");

                  float x_pos = position["x"].GetFloat();
                  float y_pos = position["y"].GetFloat();

                  controller_positions[index].x_ = x_pos * glm::cos(global_angle) - y_pos * glm::sin(global_angle);
                  controller_positions[index].y_ = x_pos * glm::sin(global_angle) + y_pos * glm::cos(global_angle);
                  controller_rotations[index].angle_ = (-position["o"].GetFloat() + 60.0f) / 180.0f * 3.14159f + global_angle;
                  controller_scales[index].w_ = side_length;
                  controller_scales[index].h_ = side_length;

                  if (controller_positions[index].x_ < x_min)
                    x_min = controller_positions[index].x_;

                  if (controller_positions[index].x_ > x_max)
                    x_max = controller_positions[index].x_;

                  if (controller_positions[index].y_ < y_min)
                    y_min = controller_positions[index].y_;

                  if (controller_positions[index].y_ > y_max)
                    y_max = controller_positions[index].y_;
                }
              }
            }

            float x_adjustment = -(x_max + x_min) / 2.0f;
            float y_adjustment = -(y_max + y_min) / 2.0f;

            for (unsigned i = 0; i < triangle_pool->size_; ++i)
            {
              triangle_positions[i].x_ += x_adjustment + 855.0f;
              triangle_positions[i].y_ += y_adjustment + 360.0f;
            }

            for (unsigned i = 0; i < controller_pool->size_; ++i)
            {
              controller_positions[i].x_ += x_adjustment + 855.0f;
              controller_positions[i].y_ += y_adjustment + 360.0f;
            }
          }
        }
      }
    }
  }

  void State_Main::SetColor()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/state";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    unsigned hue = static_cast<unsigned>(color_.x * 360);
    unsigned saturation = static_cast<unsigned>(color_.y * 100);
    unsigned brightness = static_cast<unsigned>(color_.z * 100);

    std::string request_body;

    request_body = "{\"on\":{\"value\": true}, \"hue\":{\"value\":" + std::to_string(hue) + "}, \"sat\":{\"value\":" + std::to_string(saturation) + "}, \"brightness\":{\"value\":" + std::to_string(brightness) + "}}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetHue()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/state";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    unsigned hue = static_cast<unsigned>(color_.x * 360);

    std::string request_body;

    request_body = "{\"on\":{\"value\": true}, \"hue\":{\"value\":" + std::to_string(hue) + "}}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetSaturation()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/state";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    unsigned saturation = static_cast<unsigned>(color_.y * 100);

    std::string request_body;

    request_body = "{\"on\":{\"value\": true}, \"sat\":{\"value\":" + std::to_string(saturation) + "}}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetBrightness()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/state";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    unsigned brightness = static_cast<unsigned>(color_.z * 100);

    std::string request_body;

    request_body = "{\"on\":{\"value\": true}, \"brightness\":{\"value\":" + std::to_string(brightness) + "}}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetColorTemperature()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/state";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    std::string request_body;

    request_body = "{\"on\":{\"value\": true}, \"ct\":{\"value\":" + std::to_string(colorTemperature_) + "}}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetEffect(const std::string& effect)
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/effects";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    std::string request_body;

    request_body = "{\"select\":\"" + effect + "\"}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetOnOff(bool on)
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/state";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");
    
    std::string request_body;

    request_body = "{\"on\":{\"value\":" + std::string(on ? "true" : "false") + "}}";
    
    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }

  void State_Main::SetOrientation()
  {
    std::string url = host_ + "/api/v1/" + authToken_ + "/panelLayout";

    Engine::Instance->HTTP().SetURL(url.c_str());
    Engine::Instance->HTTP().SetMethod("PUT");

    std::string request_body;

    request_body = "{\"globalOrientation\":{\"value\":" + std::to_string(orientation_) + "}}";

    Engine::Instance->HTTP().SetRequestBody(request_body.c_str());
    Engine::Instance->HTTP().SendRequest();

    GetAllPanelData();
  }
}