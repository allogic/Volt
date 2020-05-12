#pragma once

#include <Core.h>
#include <Instance.h>
#include <Watchdog.h>
#include <ModuleLoader.h>

namespace Volt
{
	enum TAssetType : u32
	{
		Module = 0,
	};

	class CAssetDatabase
		: public CInstance<CAssetDatabase>
	{
	public:
		CAssetDatabase();
		virtual ~CAssetDatabase();

		void										Update();

	private:
		void										CreateFolderIfNotExists(const std::filesystem::path& folder) const;

		void										UnloadModule(const CWatchdog::TFileSet& fileSet);
		void										LoadModule(const CWatchdog::TFileSet& fileSet);

		std::vector<CWatchdog>	mWatchdogs;

		std::filesystem::path		mModuleFolder;

		CModuleLoader						mModuleLoader;
	};
}