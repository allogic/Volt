#pragma once

#include <Core.h>
#include <Types.h>
#include <AssetType.h>

namespace Volt
{
  class CWatchdog
  {
  public:
    CWatchdog(TAssetType assetType, const std::filesystem::path& cwFolder, const std::string& extension);
    ~CWatchdog() = default;

    inline TAssetType                             AssetType() const { return mAssetType; }

    void                                          Update();

    inline const std::set<std::filesystem::path>& Files() const { return mFiles; }
    inline const std::set<std::filesystem::path>& ToDelete() const { return mToDelete; };
    inline const std::set<std::filesystem::path>& ToCreate() const { return mToCreate; };

  private:
    void                                          CheckDeletedFiles();
    void                                          CheckInsertedFiles();

    TAssetType                                    mAssetType;
    std::filesystem::path                         mCwFolder;
    std::string                                   mExtension;

    std::set<std::filesystem::path>               mFiles;

    std::set<std::filesystem::path>               mToCreate;
    std::set<std::filesystem::path>               mToDelete;
  };
}