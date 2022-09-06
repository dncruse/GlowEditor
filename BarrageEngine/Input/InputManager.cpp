/*
MIT License

Copyright(c) 2022 Dragonscale-Games

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ======================================================================== */
/*!
 * \file            InputManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Handles input events from GLFW. 

 */
/* ======================================================================== */

#include "InputManager.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <algorithm>

namespace Barrage
{
  InputManager* InputManager::manager_ = nullptr;

  InputManager::InputManager() :
    window_(nullptr),
    keysPrev_(),
    keysCurr_(),
    keysBuff_(),
    mouseLeftPrev_(false),
    mouseLeftCurr_(false),
    mouseLeftBuff_(false),
    mouseRightPrev_(false),
    mouseRightCurr_(false),
    mouseRightBuff_(false)
  {
  }

  void InputManager::Initialize(GLFWwindow* window)
  {
    // if the input manager isn't initialized and the input window is valid...
    if (!window_ && window)
    {
      // correctly size vectors and fill them with false
      keysPrev_.assign(MAX_KEY_VALUE + 2, false);
      keysCurr_.assign(MAX_KEY_VALUE + 2, false);
      keysBuff_.assign(MAX_KEY_VALUE + 2, false);
      
      window_ = window;
      manager_ = this;
      glfwSetKeyCallback(window, KeyCallback);
      glfwSetMouseButtonCallback(window, MouseCallBack);
    }
  }

  void InputManager::Update()
  {
    glfwPollEvents();
    
    keysPrev_ = keysCurr_;
    keysCurr_ = keysBuff_;

    mouseLeftPrev_ = mouseLeftCurr_;
    mouseLeftCurr_ = mouseLeftBuff_;

    mouseRightPrev_ = mouseRightCurr_;
    mouseRightCurr_ = mouseRightBuff_;
  }

  void InputManager::Shutdown()
  {
    // if the input manager is currently running...
    if (window_)
    {
      glfwSetKeyCallback(window_, nullptr);
      manager_ = nullptr;
      window_ = nullptr;
    }
  }

  bool InputManager::KeyTriggered(KEY key) const
  {
    return keysCurr_[static_cast<long long>(key) + 1] && !keysPrev_[static_cast<long long>(key) + 1];
  }

  bool InputManager::KeyIsDown(KEY key) const
  {
    return keysCurr_[static_cast<long long>(key) + 1];
  }

  bool InputManager::KeyReleased(KEY key) const
  {
    return !keysCurr_[static_cast<long long>(key) + 1] && keysPrev_[static_cast<long long>(key) + 1];
  }

  bool InputManager::MouseLeftClicked() const
  {
    return mouseLeftCurr_ && !mouseLeftPrev_;
  }

  bool InputManager::MouseRightClicked() const
  {
    return mouseRightCurr_ && !mouseRightPrev_;
  }

  MousePos InputManager::GetMousePos()
  {
    MousePos mouse_pos;
    
    glfwGetCursorPos(window_, &mouse_pos.x_, &mouse_pos.y_);

    mouse_pos.y_ = 720.0f - mouse_pos.y_;

    return mouse_pos;
  }

  void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    window;
    scancode;
    mods;

    switch (action)
    {
      case GLFW_PRESS:
        manager_->keysBuff_[static_cast<long long>(key) + 1] = true;
        break;

      case GLFW_RELEASE:
        manager_->keysBuff_[static_cast<long long>(key) + 1] = false;
        break;
    }
  }

  void InputManager::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
  {
    window;
    mods;

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      if (action == GLFW_PRESS)
        manager_->mouseLeftBuff_ = true;
      else
        manager_->mouseLeftBuff_ = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      if (action == GLFW_PRESS)
        manager_->mouseRightBuff_ = true;
      else
        manager_->mouseRightBuff_ = false;
    }
  }
}