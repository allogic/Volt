#include <ShaderLoader.h>

s32 Volt::CShaderLoader::Unload(const std::filesystem::path& file)
{
  const auto it = std::find_if(mShaders.cbegin(), mShaders.cend(), [file](const auto& shaderInfo) { return shaderInfo.file == file; });

  if (it == mShaders.cend()) return 0;

  const auto shaderInfo = *it;

  glDeleteProgram(shaderInfo.program);

  return 1;
}

s32 Volt::CShaderLoader::Load(const std::filesystem::path& file)
{
  std::fstream fileStream;

  fileStream.open(file.string().c_str());

  if (!fileStream.is_open()) return 0;

  std::stringstream stringStream;
  std::string line;

  while (std::getline(fileStream, line))
  {
    stringStream << line << '\n';
  }

  fileStream.close();

  std::string shaderSource(stringStream.str());

  std::size_t vertexPos = shaderSource.find("#vertex");
  std::size_t fragmentPos = shaderSource.find("#fragment");

  if (vertexPos == std::string::npos || fragmentPos == std::string::npos) return 0;

  std::string vertexSource(shaderSource.substr(vertexPos + 7, fragmentPos - 9));
  std::string fragmentSource(shaderSource.substr(fragmentPos + 9, shaderSource.size() - 1));

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  if (!CompileShader(vertexShader, vertexSource))
  {
    glDeleteShader(vertexShader);

    return 0;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  if (!CompileShader(fragmentShader, fragmentSource))
  {
    glDeleteShader(fragmentShader);

    return 0;
  }

  GLuint program = glCreateProgram();

  if (!LinkShaders(program, vertexShader, fragmentShader))
  {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteProgram(program);

    return 0;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  mShaders.emplace_back(
    program,
    file
  );

  return 1;
}

s32 Volt::CShaderLoader::CompileShader(GLuint shader, const std::string& source)
{
  const char* pSource = source.c_str();

  glShaderSource(shader, 1, &pSource, nullptr);
  glCompileShader(shader);

  std::string log;

  if (!CheckStatus(shader, GL_COMPILE_STATUS, log))
  {
    VOLT_TRACE(log);

    return 0;
  }

  return 1;
}

s32 Volt::CShaderLoader::LinkShaders(GLuint program, GLuint vertexShader, GLuint fragmentShader)
{
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  std::string log;

  if (!CheckStatus(program, GL_LINK_STATUS, log))
  {
    VOLT_TRACE(log);

    return 0;
  }

  return 1;
}

s32 Volt::CShaderLoader::CheckStatus(GLuint shader, GLenum type, std::string& log)
{
  GLint compileInfo;
  GLint compileInfoSize;

  glGetShaderiv(shader, type, &compileInfo);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &compileInfoSize);

  if (compileInfoSize > 0)
  {
    log.resize(compileInfoSize);

    glGetShaderInfoLog(shader, compileInfoSize, nullptr, &log[0]);

    return 0;
  }

  return 1;
}