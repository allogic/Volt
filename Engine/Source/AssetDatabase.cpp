#include <AssetDatabase.h>

Volt::CAssetDatabase::CAssetDatabase(const std::filesystem::path& streamingFolder)
	: mStreamingFolder(streamingFolder)
{
	if (!std::filesystem::is_directory(mStreamingFolder))
		std::filesystem::create_directory(mStreamingFolder);
}

Volt::CAssetDatabase::~CAssetDatabase()
{
	for (const auto& watchdog : mWatchdogs)
	{
		switch (watchdog.AssetType().type)
		{
		case TAssetType::Module:
			UnloadModule(watchdog.AllFiles());
			break;
		}
	}
}

void Volt::CAssetDatabase::Update()
{
	for (auto& watchdog : mWatchdogs)
	{
		watchdog.Update();

		switch (watchdog.AssetType().type)
		{
		case TAssetType::Module:
			UnloadModule(watchdog.FilesToDelete());
			LoadModule(watchdog.FilesToCreate());
			break;
		default:
			break;
		}
	}
}

void Volt::CAssetDatabase::UnloadModule(const CWatchdog::TFileSet& fileSet)
{
	for (const auto& srcFile : fileSet)
	{
		const auto destFile = mStreamingFolder / srcFile.filename();

		if (!mModuleLoader.Unload(destFile))
			VOLT_TRACE("Failed unloading module " << destFile);

		std::filesystem::remove(destFile);
	}
}

void Volt::CAssetDatabase::LoadModule(const CWatchdog::TFileSet& fileSet)
{
	for (const auto& srcFile : fileSet)
	{
		const auto destFile = mStreamingFolder / srcFile.filename();

		std::filesystem::copy_file(srcFile, destFile, std::filesystem::copy_options::overwrite_existing);

		if (!mModuleLoader.Load(destFile))
			VOLT_TRACE("Failed loading module " << destFile);
	}
}