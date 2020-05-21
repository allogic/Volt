#pragma once

#include <Core.h>
#include <Instance.h>
#include <Watchdog.h>
#include <AssetType.h>
#include <ModuleLoader.h>
#include <ShaderLoader.h>
#include <ModuleInfo.h>
#include <ShaderInfo.h>

namespace Volt
{
  class CAssetDatabase
    : public CInstance<CAssetDatabase>
  {
  public:
    CAssetDatabase();
    virtual ~CAssetDatabase();

    void                       Update();

    inline CModuleLoader&      Modules() { return mModuleLoader; }
    inline CShaderLoader&      Shaders() { return mShaderLoader; }

  private:
    std::filesystem::path      AssetPathFromAssetType(TAssetType type);
    std::filesystem::path      ObservedPathFromAssetType(TAssetType type);

    void                       UnloadModule(const std::set<std::filesystem::path>& fileSet);
    void                       LoadModule(const std::set<std::filesystem::path>& fileSet);

    std::vector<CWatchdog>     mWatchdogs;

    std::filesystem::path      mObservedFolder;
    std::filesystem::path      mAssetFolder;

    CModuleLoader              mModuleLoader;
    CShaderLoader              mShaderLoader;
  };
}