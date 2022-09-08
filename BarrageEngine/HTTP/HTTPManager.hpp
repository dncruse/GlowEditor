/* ======================================================================== */
/*!
 * \file            HTTPManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Curlpp wrapper class.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef HTTPManager_BARRAGE_H
#define HTTPManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "curl/curl.h"

namespace Barrage
{
	//! Curlpp wrapper class
  class HTTPManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      HTTPManager();

      /**************************************************************/
      /*!
        \brief
          Initializes curlpp and HTTP request.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Shuts down curlpp and HTTP request.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Sets the URL that requests will be sent to.

        \param url
          The url to send requests to.
      */
      /**************************************************************/
      void SetURL(const char* url);

      /**************************************************************/
      /*!
        \brief
          Sets the request body for POST and PUT requests.

        \param body
          The string version of the JSON request body to send.
      */
      /**************************************************************/
      void SetRequestBody(const char* body);

      /**************************************************************/
      /*!
        \brief
          Sets the method to use for the http request.

        \param method
          The method to use. Should be all caps.
      */
      /**************************************************************/
      void SetMethod(const char* method);

      /**************************************************************/
      /*!
        \brief
          Sends the current HTTP Request.
      */
      /**************************************************************/
      void SendRequest();

      /**************************************************************/
      /*!
        \brief
          Gets the response from the last HTTP request.

        \return
          Returns the response in string form.
      */
      /**************************************************************/
      const std::string& GetResponse();

      /**************************************************************/
      /*!
        \brief
          Gets the response code from the last HTTP request.

        \return
          Returns the response code.
      */
      /**************************************************************/
      long GetResponseCode();

    private:
      static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);

    private:
      CURL* handle_;
      
      static std::string response_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // HTTPManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////