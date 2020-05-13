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
	std::filesystem::create_directory(AssetPathFromAssetType(TAssetType::Module));

	if (!std::filesystem::is_directory(ObservedPathFromAssetType(TAssetType::Module)))
	{
		VOLT_TRACE("Module path to observe from points to no directory");
		VOLT_EXIT;
	}
	if (!std::filesystem::is_directory(AssetPathFromAssetType(TAssetType::Module)))
	{
		VOLT_TRACE("Module asset path points to no directory");
		VOLT_EXIT;
	}

	mWatchdogs.emplace_back(
		Volt::TAssetType::Module,
		ObservedPathFromAssetType(Volt::TAssetType::Module),
		".dll"
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

std::set<Volt::CModule*> Volt::CAssetDatabase::Modules() const
{
	std::set<CModule*> modules;

	for (const auto& [id, module] : mModuleLoader.mModules)
		modules.emplace(module.pModule.get());

	return modules;
}

Volt::CModule* Volt::CAssetDatabase::ModuleById(const std::string& id) const
{
	const auto it = mModuleLoader.mModules.find(id);

	return it == mModuleLoader.mModules.cend() ? nullptr : it->second.pModule.get();
}

std::filesystem::path Volt::CAssetDatabase::AssetPathFromAssetType(TAssetType type)
{
	switch (type)
	{
	case Volt::TAssetType::Module: return mAssetFolder / "Modules";
	default: return mAssetFolder;
	}
}

std::filesystem::path Volt::CAssetDatabase::ObservedPathFromAssetType(TAssetType type)
{
	switch (type)
	{
	case Volt::TAssetType::Module: return mObservedFolder / "Modules";
	default: return mObservedFolder;
	}
}

void Volt::CAssetDatabase::UnloadModule(const CWatchdog::TFileSet& fileSet)
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

void Volt::CAssetDatabase::LoadModule(const CWatchdog::TFileSet& fileSet)
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