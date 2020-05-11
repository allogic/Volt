#include <Watchdog.h>

Volt::CWatchdog::CWatchdog(const TAssetType& assetType)
	: mAssetType(assetType)
{

}

void Volt::CWatchdog::Update()
{
	DeleteFiles();
	InsertFiles();
}

void Volt::CWatchdog::DeleteFiles()
{
	mToDelete.clear();

	std::erase_if(mFiles, [&](const auto& file) {
		const auto exists = std::filesystem::exists(file);

		if (!exists) mToDelete.emplace(file);

		return !exists;
		});
}

void Volt::CWatchdog::InsertFiles()
{
	mToCreate.clear();

	for (const auto it : std::filesystem::directory_iterator(mAssetType.folder))
	{
		const auto file = it.path();

		if (file.extension() != mAssetType.extension) continue;
		if (mFiles.find(file) != mFiles.cend()) continue;

		mFiles.emplace(file);
		mToCreate.emplace(file);
	}
}