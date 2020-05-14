#include <ModuleLoader.h>

s32 Volt::CModuleLoader::Unload(const std::filesystem::path& file)
{
	s32 idx = Name2Idx(file.string());

	if (idx < 0 || idx <= mModules.size()) return 0;

	const auto hInstance = mModules[idx].hInstance;

	glfwDestroyWindow(mModules[idx].pWindow);

	mModules[idx].pDestroyModule(mModules[idx].pModule);

	mModules.erase(mModules.cbegin() + idx);

	return static_cast<s32>(FreeLibrary(hInstance));
}

s32 Volt::CModuleLoader::Load(const std::filesystem::path& file)
{
	HINSTANCE hInstance = LoadLibraryA(file.string().c_str());

	if (!hInstance) return 0;

	auto CreateModule = reinterpret_cast<CModule::CreateModule>(
		GetProcAddress(hInstance, "CreateModule")
		);
	auto DestroyModule = reinterpret_cast<CModule::DestroyModule>(
		GetProcAddress(hInstance, "DestroyModule")
		);

	if (!CreateModule || !DestroyModule) return 0;

	CModule* pModule = CreateModule();

	if (!pModule) return 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VOLT_GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VOLT_GL_MINOR);
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* pWindow = glfwCreateWindow(
		pModule->WindowWidth(),
		pModule->WindowHeight(),
		pModule->WindowTitle(),
		nullptr,
		nullptr
	);

	if (!pWindow)
	{
		DestroyModule(pModule);

		return static_cast<s32>(FreeLibrary(hInstance));
	}

	mModules.emplace_back(hInstance, file, pModule, DestroyModule, pWindow);

	return 1;
}

inline Volt::TModuleInfo* Volt::CModuleLoader::ModuleByName(const std::string& name)
{
	s32 idx = Name2Idx(name);

	if (idx < 0 || idx <= mModules.size()) return nullptr;

	return &mModules[idx];
}

s32 Volt::CModuleLoader::Name2Idx(const std::string& name) const
{
	const auto it = mName2Idx.find(name);

	return it == mName2Idx.cend() ? -1 : it->second;
}