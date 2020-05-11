#pragma once

#include <Core.h>
#include <Instance.h>
#include <Watchdog.h>
#include <AssetType.h>
#include <ModuleLoader.h>

namespace Volt
{
	class CAssetDatabase final
		: public CInstance<CAssetDatabase>
	{
	public:
		CAssetDatabase(const std::filesystem::path& streamingFolder);
		~CAssetDatabase();

		inline void							RegisterAssetType(const TAssetType& assetType) { mWatchdogs.emplace_back(assetType); }
		void										Update();

	private:
		void										UnloadModule(const CWatchdog::TFileSet& fileSet);
		void										LoadModule(const CWatchdog::TFileSet& fileSet);

		std::filesystem::path		mStreamingFolder;

		std::vector<CWatchdog>	mWatchdogs;

		CModuleLoader						mModuleLoader;
	};
}