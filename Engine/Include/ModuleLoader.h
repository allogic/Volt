#pragma once

#include <Core.h>

namespace Volt
{
	class CModuleLoader final
	{
	public:
		using TModuleInstance = std::tuple<HINSTANCE, std::unique_ptr<CModule, CModule::DestroyModule>>;

		CModuleLoader() = default;
		~CModuleLoader() = default;

		s32																			Unload(const std::filesystem::path& file);
		s32																			Load(const std::filesystem::path& file);

	private:
		std::map<std::filesystem::path, TModuleInstance>	mInstances;
	};
}