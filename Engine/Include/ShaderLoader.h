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
    s32                            CompileShader(GLuint shader, const std::string& source);
    s32                            LinkShaders(GLuint program, GLuint vertexShader, GLuint fragmentShader);

    s32                            CheckStatus(GLuint shader, GLenum type, std::string& log);

    std::vector<TShaderInfo>       mShaders;
  };
}