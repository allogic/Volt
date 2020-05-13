#pragma once

#include <Core.h>
#include <Instance.h>
#include <Watchdog.h>
#include <ModuleLoader.h>
#include <AssetType.h>

namespace Volt
{
	class CAssetDatabase
		: public CInstance<CAssetDatabase>
	{
	public:
		CAssetDatabase();
		virtual ~CAssetDatabase();

		void															Update();

		std::set<CModule*>								Modules() const;
		CModule*													ModuleById(const std::string& id) const;

	private:
		std::filesystem::path							AssetPathFromAssetType(TAssetType type);
		std::filesystem::path							ObservedPathFromAssetType(TAssetType type);

		void															UnloadModule(const CWatchdog::TFileSet& fileSet);
		void															LoadModule(const CWatchdog::TFileSet& fileSet);

		std::vector<CWatchdog>						mWatchdogs;

		std::filesystem::path							mObservedFolder;
		std::filesystem::path							mAssetFolder;

		CModuleLoader											mModuleLoader;
	};
}