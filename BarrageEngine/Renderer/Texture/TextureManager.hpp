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
 * \file            TextureManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture manager class for renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TextureManager_BARRAGE_H
#define TextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Texture.hpp"

#include <unordered_map>
#include <string>

namespace Barrage
{
  class Texture;

  typedef std::unordered_map<std::string, Texture*> TextureLibrary;

  //! Temporary texture manager to make it convenient to test game systems.
  class TextureManager
  {
  public:
    TextureManager();

    ~TextureManager();

    TextureManager(TextureManager& other) = delete;

    void operator=(const TextureManager& rhs) = delete;

    const Texture* GetTexture(const std::string& name);

    void LoadTexture(const std::string& name);

    void UnloadTexture(const std::string& name);

  private:
    TextureLibrary library_;

    Texture* CreateTexture(const std::string& name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////