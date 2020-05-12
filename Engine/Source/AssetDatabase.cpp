#include <AssetDatabase.h>

Volt::CAssetDatabase::CAssetDatabase()
{
	const auto cwFolder = std::filesystem::current_path();
	const auto tmpFolder = std::filesystem::temp_directory_path() / "Volt/Assets";

	mModuleFolder = tmpFolder / "Modules";

	CreateFolderIfNotExists(tmpFolder);
	CreateFolderIfNotExists(mModuleFolder);

	mWatchdogs.emplace_back(TAssetType::Module, cwFolder, ".dll");
}

Volt::CAssetDatabase::~CAssetDatabase()
{
	for (const auto& watchdog : mWatchdogs)
	{
		switch (watchdog.AssetType())
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

		switch (watchdog.AssetType())
		{
		case TAssetType::Module:
			UnloadModule(watchdog.ToDelete());
			LoadModule(watchdog.ToCreate());
			break;
		default:
			break;
		}
	}
}

void Volt::CAssetDatabase::CreateFolderIfNotExists(const std::filesystem::path& folder) const
{
	if (!std::filesystem::is_directory(folder))
		std::filesystem::create_directory(folder);
}

void Volt::CAssetDatabase::UnloadModule(const CWatchdog::TFileSet& fileSet)
{
	for (const auto& srcFile : fileSet)
	{
		const auto destFile = mModuleFolder / srcFile.filename();

		if (!mModuleLoader.Unload(destFile))
			VOLT_TRACE("Failed unloading module " << destFile);

		std::filesystem::remove(destFile);
	}
}

void Volt::CAssetDatabase::LoadModule(const CWatchdog::TFileSet& fileSet)
{
	for (const auto& srcFile : fileSet)
	{
		const auto destFile = mModuleFolder / srcFile.filename();

		std::filesystem::copy_file(srcFile, destFile, std::filesystem::copy_options::overwrite_existing);

		if (!mModuleLoader.Load(destFile))
			VOLT_TRACE("Failed loading module " << destFile);
	}
}