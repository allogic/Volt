#pragma once

#include <Core.h>
#include <Types.h>
#include <Module.h>
#include <ModuleInfo.h>

namespace Volt
{
  class CModuleLoader
  {
  public:
    VOLT_DECLARE_ITERABLE(mModules);

    CModuleLoader() = default;
    ~CModuleLoader() = default;

    s32                            Unload(const std::filesystem::path& file);
    s32                            Load(const std::filesystem::path& file);

  private:
    std::vector<TModuleInfo>       mModules;
  };
}