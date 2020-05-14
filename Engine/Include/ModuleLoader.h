#pragma once

#include <Core.h>
#include <Types.h>
#include <Module.h>
#include <ModuleInfo.h>

namespace Volt
{
	class CModuleLoader
	{
	public:
		CModuleLoader() = default;
		~CModuleLoader() = default;

		s32																		Unload(const std::filesystem::path& file);
		s32																		Load(const std::filesystem::path& file);

		inline std::vector<TModuleInfo>				Modules() { return mModules; };
		inline TModuleInfo*										ModuleByName(const std::string& name);

		s32																		Name2Idx(const std::string& name) const;

	private:
		std::vector<TModuleInfo>							mModules;

		std::map<std::string, s32>						mName2Idx;
	};
}