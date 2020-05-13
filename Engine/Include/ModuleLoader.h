#pragma once

#include <Core.h>
#include <Module.h>

namespace Volt
{
	class CModuleLoader
	{
	public:
		friend class CAssetDatabase;

		using TModulePtr = std::unique_ptr<CModule, CModule::DestroyModule>;

		struct TModuleInfo
		{
			HINSTANCE hInstance;
			std::filesystem::path file;
			TModulePtr pModule;
		};

		using TModuleMap = std::map<std::string, TModuleInfo>;

		CModuleLoader() = default;
		~CModuleLoader() = default;

		s32										Unload(const std::filesystem::path& file);
		s32										Load(const std::filesystem::path& file);

	private:
		TModuleMap						mModules;
	};
}