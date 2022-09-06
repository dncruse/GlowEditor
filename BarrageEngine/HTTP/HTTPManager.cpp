/* ======================================================================== */
/*!
 * \file            HTTPManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Curlpp wrapper class.
 */
/* ======================================================================== */

#include "HTTPManager.hpp"
#include <iostream>

namespace Barrage
{
  std::string HTTPManager::response_ = std::string();
  
  HTTPManager::HTTPManager() :
    handle_(nullptr)
  {
  }

  void HTTPManager::Initialize()
  {
    curl_global_init(CURL_GLOBAL_ALL);

    handle_ = curl_easy_init();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: text/plain");
    curl_easy_setopt(handle_, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(handle_, CURLOPT_WRITEDATA, &response_);
  }

  void HTTPManager::Shutdown()
  {
    delete handle_;
    
    curl_global_cleanup();
  }

  void HTTPManager::SetURL(const std::string& url)
  {
    curl_easy_setopt(handle_, CURLOPT_URL, url.c_str());
  }

  void HTTPManager::SetRequestBody(const std::string& body)
  {
    curl_easy_setopt(handle_, CURLOPT_POSTFIELDS, body.c_str());
    //curl_easy_setopt(handle_, CURLOPT_POSTFIELDSIZE, body.length() + 1);
  }

  void HTTPManager::SetMethod(const std::string& method)
  {
    curl_easy_setopt(handle_, CURLOPT_CUSTOMREQUEST, method.c_str());
  }

  void HTTPManager::SendRequest()
  {
    response_ = std::string();
    curl_easy_perform(handle_);
  }

  const std::string& HTTPManager::GetResponse()
  {
    return response_;
  }

  size_t HTTPManager::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
  {
    size_t newLength = size * nmemb;

    try
    {
      response->append((char*)contents, newLength);
    }
    catch (std::bad_alloc& e)
    {
      std::cout << "Exception in WriteCallback: " << e.what() << std::endl;

      return 0;
    }

    return newLength;
  }
}