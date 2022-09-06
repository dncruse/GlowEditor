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
 * \file            Renderer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Simple renderer, good for debugging or demo projects.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Renderer_BARRAGE_H
#define Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <string>

#include "Shader/ShaderManager.hpp"
#include "Texture/TextureManager.hpp"

struct GLFWwindow;

namespace Barrage
{
  const std::string default_texture = std::string();
  const std::string default_shader = std::string();

  //! Toy renderer for testing game systems
  class Renderer
  {
  public:
    Renderer();

    void Initialize();

    void Shutdown();

    void StartFrame();

    void EndFrame();

    bool WindowClosed();

    GLFWwindow* GetWindowHandle();

    void Draw(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::string& texture = default_texture, const glm::vec4& tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void Draw(const glm::mat4& transform, const std::string& texture = default_texture, const glm::vec4 & tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void DrawInstanced(const glm::vec2* positionArray, float* rotationArray, const glm::vec2* scaleArray, unsigned instances, const std::string& texture = default_texture);

  private:
    GLFWwindow* window_;

    ShaderManager shaderManager_;
    TextureManager textureManager_;

    const Texture* boundTexture_;
    const Shader* boundShader_;
    
    glm::mat4 viewMat_;
    glm::mat4 projMat_;

    unsigned vao_;
    unsigned vertexBuffer_;
    unsigned faceBuffer_;
    unsigned translationBuffer_;
    unsigned scaleBuffer_;
    unsigned rotationBuffer_;

    int transformUniform_;
    int tintUniform_;
    int viewUniform_;
    int projectionUniform_;
    int textureUniform_;

    void CreateGLFWWindow();

    void SetBackgroundColor(const glm::vec4& color);

    void LoadGLFunctions();

    void GetUniformLocations();

    void SetUniforms();

    void CreateQuadMesh();

    void EnableBlending();

    void BindTexture(const std::string& textureName);

    void BindShader(const std::string& shader_name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////