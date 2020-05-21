#pragma once

#include <Core.h>

namespace Volt
{
  struct TShaderInfo
  {
    TShaderInfo(
      std::filesystem::path file
    )
      : file(file) {}

    std::filesystem::path    file;
  };
}