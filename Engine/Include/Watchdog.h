#pragma once

#include <Core.h>
#include <AssetType.h>

namespace Volt
{
	class CWatchdog
	{
	public:
		using TFileSet = std::set<std::filesystem::path>;

		CWatchdog(TAssetType assetType, const std::filesystem::path& cwFolder, const std::string& extension);
		~CWatchdog() = default;

		inline TAssetType					AssetType() const { return mAssetType; }

		void											Update();

		inline const TFileSet&		Files() const { return mFiles; }
		inline const TFileSet&		ToDelete() const { return mToDelete; };
		inline const TFileSet&		ToCreate() const { return mToCreate; };

	private:
		void											CheckDeletedFiles();
		void											CheckInsertedFiles();

		TAssetType								mAssetType;
		std::filesystem::path			mCwFolder;
		std::string								mExtension;

		TFileSet									mFiles;

		TFileSet									mToCreate;
		TFileSet									mToDelete;
	};
}