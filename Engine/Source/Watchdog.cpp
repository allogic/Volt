#include <Watchdog.h>

Volt::CWatchdog::CWatchdog(const std::filesystem::path& folder, const std::string& extension)
  : mFolder(folder)
  , mExtension(extension)
{

}

void Volt::CWatchdog::Update()
{
  CheckDeletedFiles();
  CheckChangedFiles();
  CheckInsertedFiles();
}

const Volt::CWatchdog::TFileSet& Volt::CWatchdog::AllFiles()
{
  mAllFiles.clear();

  for (const auto& [file, time] : mFileInfos)
  {
    mAllFiles.emplace(file);
  }

  return mAllFiles;
}

void Volt::CWatchdog::CheckDeletedFiles()
{
  mToDelete.clear();

  std::erase_if(mFileInfos, [&](const auto& fileInfo) {
    const auto& file = fileInfo.first;

    const auto exists = std::filesystem::exists(file);

    if (!exists) mToDelete.emplace(file);

    return !exists;
    });
}

void Volt::CWatchdog::CheckInsertedFiles()
{
  mToCreate.clear();

  for (const auto it : std::filesystem::directory_iterator(mFolder))
  {
    const auto file = it.path();

    if (file.extension() != mExtension) continue;
    if (mFileInfos.find(file) != mFileInfos.cend()) continue;

    mFileInfos.emplace(file, std::filesystem::last_write_time(file));
    mToCreate.emplace(file);
  }
}

void Volt::CWatchdog::CheckChangedFiles()
{
  mToChange.clear();

  for (auto& [file, prevTime] : mFileInfos)
  {
    const auto time = std::filesystem::last_write_time(file);

    if (time > prevTime)
    {
      prevTime = time;

      mToChange.emplace(file);
    }
  }
}