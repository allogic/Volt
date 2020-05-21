#pragma once

#include <Core.h>

namespace Volt
{
  template<typename T>
  class CInstance
  {
  public:
    CInstance() = default;
    virtual ~CInstance() = default;

    static T& Instance()
    {
      if (!pInstance) pInstance = new T;

      return *pInstance;
    }

    template<typename ... Args>
    static T& Instance(Args&&... args)
    {
      if (!pInstance) pInstance = new T(std::forward<Args>(args)...);

      return *pInstance;
    }

    static void Delete()
    {
      if (pInstance) delete pInstance;
    }

  private:
    static inline T* pInstance = nullptr;
  };
}