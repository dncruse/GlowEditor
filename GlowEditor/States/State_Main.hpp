/* ======================================================================== */
/*!
 * \file            State_Main.hpp
 * \par             Glow Editor
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com
 * \brief
   The main application state for Glow Editor.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef State_Main_BARRAGE_H
#define State_Main_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <State/State.hpp>
#include <Engine/Engine.hpp>

#include <rapidjson/document.h>

namespace rj = rapidjson;

namespace Glow
{
  //! main application state for Glow Editor
  class State_Main : public Barrage::State
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Sets the three state functions to the static Enter,
          Update, and Exit functions below.
      */
      /**************************************************************/
      State_Main();

      static void ReadConfigFile();

      static void WriteConfigFile();

    private:
      /**************************************************************/
      /*!
        \brief
          The enter function is called once when the gamestate is
          entered. It is optional.
      */
      /**************************************************************/
      static void Enter();

      /**************************************************************/
      /*!
        \brief
          The enter function is called once when the gamestate is
          entered. It must be defined.
      */
      /**************************************************************/
      static void Update();

      /**************************************************************/
      /*!
        \brief
          The exit function is called once when the gamestate is
          exited. It is optional.
      */
      /**************************************************************/
      static void Exit();

      static void MakeEditorWidget();

      static void SetLightColor();

      static void SetLightToDefault();

      static void GetAllShapeData();

    private:
      static glm::vec3 color_;          //!< the current color of the lights
      static rj::Document lightConfig_; //!< light configuration JSON
      static long long timer_;          //!< update timer
      static std::string authToken_;    //!< auth token
      static std::string host_;         //!< host IP address
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // State_Main_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////