#pragma once

#include <Core.h>
#include <Types.h>
#include <ShaderInfo.h>

namespace Volt
{
  class CShaderLoader
  {
  public:
    VOLT_DECLARE_ITERABLE(mShaders);

    CShaderLoader() = default;
    ~CShaderLoader() = default;

    s32                            Unload(const std::filesystem::path& file);
    s32                            Load(const std::filesystem::path& file);

  private:
    std::vector<TShaderInfo>       mShaders;
  };
}