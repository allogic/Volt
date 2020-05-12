#include <Watchdog.h>

Volt::CWatchdog::CWatchdog(const TAssetType& assetType, const std::filesystem::path& cwFolder, const std::string& extension)
	: mAssetType(assetType)
	, mCwFolder(cwFolder)
	, mExtension(extension)
{

}

void Volt::CWatchdog::Update()
{
	CheckDeletedFiles();
	CheckInsertedFiles();
}

void Volt::CWatchdog::CheckDeletedFiles()
{
	mToDelete.clear();

	std::erase_if(mFiles, [&](const auto& file) {
		const auto exists = std::filesystem::exists(file);

		if (!exists) mToDelete.emplace(file);

		return !exists;
		});
}

void Volt::CWatchdog::CheckInsertedFiles()
{
	mToCreate.clear();

	for (const auto it : std::filesystem::directory_iterator(mCwFolder))
	{
		const auto file = it.path();

		if (file.extension() != mExtension) continue;
		if (mFiles.find(file) != mFiles.cend()) continue;

		mFiles.emplace(file);
		mToCreate.emplace(file);
	}
}