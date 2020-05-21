#pragma once

#include <Core.h>

namespace Volt
{
  struct TShaderInfo
  {
    TShaderInfo(
      GLuint program,
      std::filesystem::path file
    )
      : program(program)
      , file(file) {}

    GLuint                   program;
    std::filesystem::path    file;
  };
}