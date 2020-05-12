#pragma once

#include <Core.h>
#include <Module.h>

namespace Volt
{
	class CModuleLoader
	{
	public:
		using TModulePtr = std::unique_ptr<CModule, CModule::DestroyModule>;
		using TModuleInstance = std::tuple<HINSTANCE, TModulePtr>;
		using TModuleInstanceMap = std::map<std::filesystem::path, TModuleInstance>;

		CModuleLoader() = default;
		~CModuleLoader() = default;

		s32									Unload(const std::filesystem::path& file);
		s32									Load(const std::filesystem::path& file);

	private:
		TModuleInstanceMap	mInstances;
	};
}