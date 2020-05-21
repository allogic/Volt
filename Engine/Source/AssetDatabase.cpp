#include <AssetDatabase.h>

Volt::CAssetDatabase::CAssetDatabase()
{
  const char* observedPathEnv = VOLT_OBSERVED_PATH;
  const char* assetPathEnv = VOLT_ASSET_PATH;

  mObservedFolder = observedPathEnv ? observedPathEnv : "";
  mAssetFolder = assetPathEnv ? assetPathEnv : "";

  if (!std::filesystem::is_directory(mObservedFolder))
  {
    VOLT_TRACE("Observed path points to no directory");
    VOLT_EXIT;
  }

  std::filesystem::create_directory(mAssetFolder);

  if (!std::filesystem::is_directory(mAssetFolder))
  {
    VOLT_TRACE("Asset path points to no directory");
    VOLT_EXIT;
  }

  std::filesystem::create_directory(ObservedPathFromAssetType(TAssetType::Module));
  std::filesystem::create_directory(ObservedPathFromAssetType(TAssetType::Shader));

  std::filesystem::create_directory(AssetPathFromAssetType(TAssetType::Module));
  std::filesystem::create_directory(AssetPathFromAssetType(TAssetType::Shader));

  if (!std::filesystem::is_directory(ObservedPathFromAssetType(TAssetType::Module)))
  {
    VOLT_TRACE("Module path to observe from points to no directory");
    VOLT_EXIT;
  }
  else if (!std::filesystem::is_directory(ObservedPathFromAssetType(TAssetType::Shader)))
  {
    VOLT_TRACE("Shader path to observe from points to no directory");
    VOLT_EXIT;
  }

  if (!std::filesystem::is_directory(AssetPathFromAssetType(TAssetType::Module)))
  {
    VOLT_TRACE("Module asset path points to no directory");
    VOLT_EXIT;
  }
  else if (!std::filesystem::is_directory(AssetPathFromAssetType(TAssetType::Shader)))
  {
    VOLT_TRACE("Shader asset path points to no directory");
    VOLT_EXIT;
  }

  mModuleWatchdog = std::make_unique<CWatchdog>(ObservedPathFromAssetType(TAssetType::Module), ".dll");
  mShaderWatchdog = std::make_unique<CWatchdog>(ObservedPathFromAssetType(TAssetType::Shader), ".glsl");
}

Volt::CAssetDatabase::~CAssetDatabase()
{
  UnloadModule(mModuleWatchdog->AllFiles());
  UnloadShader(mShaderWatchdog->AllFiles());
}

void Volt::CAssetDatabase::UpdateModules()
{
  mModuleWatchdog->Update();

  UnloadModule(mModuleWatchdog->ToDelete());
  UpdateModule(mModuleWatchdog->ToChange());
  LoadModule(mModuleWatchdog->ToCreate());
}

void Volt::CAssetDatabase::UpdateShaders()
{
  mShaderWatchdog->Update();

  UnloadShader(mShaderWatchdog->ToDelete());
  UpdateShader(mShaderWatchdog->ToChange());
  LoadShader(mShaderWatchdog->ToCreate());
}

std::filesystem::path Volt::CAssetDatabase::AssetPathFromAssetType(TAssetType type)
{
  switch (type)
  {
  case Volt::TAssetType::Module: return mAssetFolder / "Modules";
  case Volt::TAssetType::Shader: return mAssetFolder / "Shaders";
  default: return mAssetFolder;
  }
}

std::filesystem::path Volt::CAssetDatabase::ObservedPathFromAssetType(TAssetType type)
{
  switch (type)
  {
  case Volt::TAssetType::Module: return mObservedFolder / "Modules";
  case Volt::TAssetType::Shader: return mObservedFolder / "Shaders";
  default: return mObservedFolder;
  }
}

void Volt::CAssetDatabase::UnloadModule(const CWatchdog::TFileSet& fileSet)
{
  for (const auto& srcFile : fileSet)
  {
    const auto destFile = AssetPathFromAssetType(TAssetType::Module) / srcFile.filename();

    if (mModuleLoader.Unload(destFile))
    {
      VOLT_TRACE("Unloading module " << destFile);
    }
    else
    {
      VOLT_TRACE("Failed unloading module " << destFile);

      std::filesystem::remove(destFile);
    }
  }
}

void Volt::CAssetDatabase::UpdateModule(const CWatchdog::TFileSet& fileSet)
{
  UnloadModule(fileSet);
  LoadModule(fileSet);
}

void Volt::CAssetDatabase::LoadModule(const CWatchdog::TFileSet& fileSet)
{
  for (const auto& srcFile : fileSet)
  {
    const auto destFile = AssetPathFromAssetType(TAssetType::Module) / srcFile.filename();

    std::filesystem::copy_file(srcFile, destFile, std::filesystem::copy_options::overwrite_existing);

    if (mModuleLoader.Load(destFile))
    {
      VOLT_TRACE("Loading module " << destFile);
    }
    else
    {
      VOLT_TRACE("Failed loading module " << destFile);

      if (std::filesystem::exists(destFile))
        std::filesystem::remove(destFile);
    }
  }
}

void Volt::CAssetDatabase::UnloadShader(const CWatchdog::TFileSet& fileSet)
{
  for (const auto& srcFile : fileSet)
  {
    const auto destFile = AssetPathFromAssetType(TAssetType::Shader) / srcFile.filename();

    if (mShaderLoader.Unload(destFile))
    {
      VOLT_TRACE("Unloading shader " << destFile);
    }
    else
    {
      VOLT_TRACE("Failed unloading shader " << destFile);

      std::filesystem::remove(destFile);
    }
  }
}

void Volt::CAssetDatabase::UpdateShader(const CWatchdog::TFileSet& fileSet)
{
  UnloadShader(fileSet);
  LoadShader(fileSet);
}

void Volt::CAssetDatabase::LoadShader(const CWatchdog::TFileSet& fileSet)
{
  for (const auto& srcFile : fileSet)
  {
    const auto destFile = AssetPathFromAssetType(TAssetType::Shader) / srcFile.filename();

    std::filesystem::copy_file(srcFile, destFile, std::filesystem::copy_options::overwrite_existing);

    if (mShaderLoader.Load(destFile))
    {
      VOLT_TRACE("Loading shader " << destFile);
    }
    else
    {
      VOLT_TRACE("Failed loading shader " << destFile);

      if (std::filesystem::exists(destFile))
        std::filesystem::remove(destFile);
    }
  }
}