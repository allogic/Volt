#pragma once

#include <Core.h>
#include <Module.h>

namespace Volt
{
	struct TModuleInfo
	{
		HINSTANCE								hInstance;
		std::filesystem::path		file;
		CModule*								pModule;
		CModule::DestroyModule	pDestroyModule;
		GLFWwindow*							pWindow;
	};
}