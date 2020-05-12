#include <Windows.h>

#include <ModuleLoader.h>

s32 Volt::CModuleLoader::Unload(const std::filesystem::path& file)
{
	const auto it = mInstances.find(file);

	if (it == mInstances.cend()) return 0;

	const auto hInstance = std::get<0>(it->second);

	mInstances.erase(file);

	const auto status = FreeLibrary(hInstance);

	return static_cast<s32>(status);
}

s32 Volt::CModuleLoader::Load(const std::filesystem::path& file)
{
	if (mInstances.find(file) != mInstances.cend()) return 0;

	HINSTANCE hInstance = LoadLibraryA(file.string().c_str());

	if (!hInstance) return 0;

	CModule::CreateModule CreateModule = reinterpret_cast<CModule::CreateModule>(
		GetProcAddress(hInstance, "CreateModule")
		);
	CModule::DestroyModule DestroyModule = reinterpret_cast<CModule::DestroyModule>(
		GetProcAddress(hInstance, "DestroyModule")
		);

	if (!CreateModule || !DestroyModule) return 0;

	mInstances.emplace(
		file,
		TModuleInstance{ hInstance, TModulePtr{CreateModule(), DestroyModule} }
	);

	return 1;
}