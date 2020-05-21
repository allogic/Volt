#pragma once

#include <Core.h>
#include <Types.h>

namespace Volt
{
  class CWatchdog
  {
  public:
    using TFileInfoMap = std::map<std::filesystem::path, std::filesystem::file_time_type>;
    using TFileSet     = std::set<std::filesystem::path>;

    CWatchdog(const std::filesystem::path& folder, const std::string& extension);
    ~CWatchdog() = default;

    void                      Update();

    const TFileSet&           AllFiles();
    inline const TFileSet&    ToDelete() const { return mToDelete; };
    inline const TFileSet&    ToCreate() const { return mToCreate; };
    inline const TFileSet&    ToChange() const { return mToChange; };

  private:
    void                      CheckDeletedFiles();
    void                      CheckInsertedFiles();
    void                      CheckChangedFiles();

    std::filesystem::path     mFolder;
    std::string               mExtension;

    TFileInfoMap              mFileInfos;

    TFileSet                  mAllFiles;
    TFileSet                  mToCreate;
    TFileSet                  mToDelete;
    TFileSet                  mToChange;
  };
}