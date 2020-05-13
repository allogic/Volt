#include <ModuleLoader.h>

s32 Volt::CModuleLoader::Unload(const std::filesystem::path& file)
{
	const auto it = mModules.find(file.string());

	if (it == mModules.cend()) return 0;

	const auto hInstance = it->second.hInstance;

	mModules.erase(it);

	return static_cast<s32>(FreeLibrary(hInstance));
}

s32 Volt::CModuleLoader::Load(const std::filesystem::path& file)
{
	if (mModules.find(file.string()) != mModules.cend()) return 0;

	HINSTANCE hInstance = LoadLibraryA(file.string().c_str());

	if (!hInstance) return 0;

	CModule::CreateModule CreateModule = reinterpret_cast<CModule::CreateModule>(
		GetProcAddress(hInstance, "CreateModule")
		);
	CModule::DestroyModule DestroyModule = reinterpret_cast<CModule::DestroyModule>(
		GetProcAddress(hInstance, "DestroyModule")
		);

	if (!CreateModule || !DestroyModule) return 0;

	auto pModule = TModulePtr{ CreateModule(), DestroyModule };

	if (!pModule.get()) return 0;

	auto moduleInfo = TModuleInfo{ hInstance, file, std::move(pModule) };

	mModules.emplace(file.string(), std::move(moduleInfo));

	return 1;
}