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

    void                       UpdateModules();
    void                       UpdateShaders();

    inline CModuleLoader&      Modules() { return mModuleLoader; }
    inline CShaderLoader&      Shaders() { return mShaderLoader; }

  private:
    std::filesystem::path      AssetPathFromAssetType(TAssetType type);
    std::filesystem::path      ObservedPathFromAssetType(TAssetType type);

    void                       UnloadModule(const CWatchdog::TFileSet& fileSet);
    void                       UpdateModule(const CWatchdog::TFileSet& fileSet);
    void                       LoadModule(const CWatchdog::TFileSet& fileSet);

    void                       UnloadShader(const CWatchdog::TFileSet& fileSet);
    void                       UpdateShader(const CWatchdog::TFileSet& fileSet);
    void                       LoadShader(const CWatchdog::TFileSet& fileSet);

    std::unique_ptr<CWatchdog> mModuleWatchdog;
    std::unique_ptr<CWatchdog> mShaderWatchdog;

    std::filesystem::path      mObservedFolder;
    std::filesystem::path      mAssetFolder;

    CModuleLoader              mModuleLoader;
    CShaderLoader              mShaderLoader;
  };
}