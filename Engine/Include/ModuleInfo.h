#pragma once

#include <Core.h>
#include <Module.h>

namespace Volt
{
  struct TModuleInfo
  {
    TModuleInfo(
      HINSTANCE hInstance,
      std::filesystem::path file,
      CModule* pModule,
      CModule::DestroyModule pDestroyModule,
      GLFWwindow* pWindow
    )
      : hInstance(hInstance)
      , file(file)
      , pModule(pModule)
      , pDestroyModule(pDestroyModule)
      , pWindow(pWindow) {}

    HINSTANCE                hInstance;
    std::filesystem::path    file;
    CModule*                 pModule;
    CModule::DestroyModule   pDestroyModule;
    GLFWwindow*              pWindow;
  };
}