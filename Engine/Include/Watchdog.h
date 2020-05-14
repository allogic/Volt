#pragma once

#include <Core.h>
#include <Types.h>

namespace Volt
{
	class CWatchdog
	{
	public:
		CWatchdog(TAssetType assetType, const std::filesystem::path& cwFolder, const std::string& extension);
		~CWatchdog() = default;

		inline TAssetType					AssetType() const { return mAssetType; }

		void											Update();

		inline const TPathSet&		Files() const { return mFiles; }
		inline const TPathSet&		ToDelete() const { return mToDelete; };
		inline const TPathSet&		ToCreate() const { return mToCreate; };

	private:
		void											CheckDeletedFiles();
		void											CheckInsertedFiles();

		TAssetType								mAssetType;
		std::filesystem::path			mCwFolder;
		std::string								mExtension;

		TPathSet									mFiles;

		TPathSet									mToCreate;
		TPathSet									mToDelete;
	};
}