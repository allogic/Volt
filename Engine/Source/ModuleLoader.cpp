#include <ModuleLoader.h>

s32 Volt::CModuleLoader::Unload(const std::filesystem::path& file)
{
	const auto it = mInstances.find(file);

	if (it == mInstances.cend()) return false;

	const auto hInstance = std::get<0>(it->second);

	mInstances.erase(file);

	return static_cast<s32>(FreeLibrary(hInstance));
}

s32 Volt::CModuleLoader::Load(const std::filesystem::path& file)
{
	if (mInstances.find(file) != mInstances.cend()) return false;

	HINSTANCE hInstance = LoadLibraryA(file.string().c_str());

	if (!hInstance) return false;

	CModule::CreateModule CreateModule = reinterpret_cast<CModule::CreateModule>(
		GetProcAddress(hInstance, "CreateModule")
		);
	CModule::DestroyModule DestroyModule = reinterpret_cast<CModule::DestroyModule>(
		GetProcAddress(hInstance, "DestroyModule")
		);

	if (!CreateModule || !DestroyModule) return false;

	mInstances.emplace(
		file,
		TModuleInstance{ hInstance, std::unique_ptr<CModule, CModule::DestroyModule>(CreateModule(), DestroyModule) }
	);

	return true;
}