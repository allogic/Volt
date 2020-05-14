#pragma once

#include <Core.h>
#include <Instance.h>
#include <Watchdog.h>
#include <ModuleLoader.h>
#include <ModuleInfo.h>

namespace Volt
{
	class CAssetDatabase
		: public CInstance<CAssetDatabase>
	{
	public:
		CAssetDatabase();
		virtual ~CAssetDatabase();

		void																	Update();

		std::vector<TModuleInfo>							Modules();
		TModuleInfo*													ModuleByName(const std::string& id);

	private:
		std::filesystem::path									AssetPathFromAssetType(TAssetType type);
		std::filesystem::path									ObservedPathFromAssetType(TAssetType type);

		void																	UnloadModule(const TPathSet& fileSet);
		void																	LoadModule(const TPathSet& fileSet);

		std::vector<CWatchdog>								mWatchdogs;

		std::filesystem::path									mObservedFolder;
		std::filesystem::path									mAssetFolder;

		CModuleLoader													mModuleLoader;
	};
}