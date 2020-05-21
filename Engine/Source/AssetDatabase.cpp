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

  mWatchdogs.emplace_back(
    Volt::TAssetType::Module,
    ObservedPathFromAssetType(Volt::TAssetType::Module),
    ".dll"
  );

  mWatchdogs.emplace_back(
    Volt::TAssetType::Shader,
    ObservedPathFromAssetType(Volt::TAssetType::Shader),
    ".glsl"
  );
}

Volt::CAssetDatabase::~CAssetDatabase()
{
  for (const auto& watchdog : mWatchdogs)
  {
    switch (watchdog.AssetType())
    {
    case Volt::TAssetType::Module:
      UnloadModule(watchdog.Files());
      break;
    }
  }
}

void Volt::CAssetDatabase::Update()
{
  for (auto& watchdog : mWatchdogs)
  {
    watchdog.Update();

    switch (watchdog.AssetType())
    {
    case Volt::TAssetType::Module:
      UnloadModule(watchdog.ToDelete());
      LoadModule(watchdog.ToCreate());
      break;
    default:
      break;
    }
  }
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

void Volt::CAssetDatabase::UnloadModule(const std::set<std::filesystem::path>& fileSet)
{
  for (const auto& srcFile : fileSet)
  {
    const auto destFile = AssetPathFromAssetType(TAssetType::Module) / srcFile.filename();

    if (!mModuleLoader.Unload(destFile))
    {
      VOLT_TRACE("Failed unloading module " << destFile);

      std::filesystem::remove(destFile);
    }
  }
}

void Volt::CAssetDatabase::LoadModule(const std::set<std::filesystem::path>& fileSet)
{
  for (const auto& srcFile : fileSet)
  {
    const auto destFile = AssetPathFromAssetType(TAssetType::Module) / srcFile.filename();

    std::filesystem::copy_file(srcFile, destFile, std::filesystem::copy_options::overwrite_existing);

    if (!mModuleLoader.Load(destFile))
    {
      VOLT_TRACE("Failed loading module " << destFile);

      if (std::filesystem::exists(destFile))
        std::filesystem::remove(destFile);
    }
  }
}