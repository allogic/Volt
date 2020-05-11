#pragma once

#include <Core.h>
#include <AssetType.h>

namespace Volt
{
	class CWatchdog final
	{
	public:
		using TFileSet = std::set<std::filesystem::path>;

		CWatchdog(const TAssetType& assetType);
		~CWatchdog() = default;

		inline const TAssetType&	AssetType() const { return mAssetType; }

		void											Update();
		TFileSet									AllFiles() const {	return mFiles; }

		inline const TFileSet&		FilesToDelete() const { return mToDelete; };
		inline const TFileSet&		FilesToCreate() const { return mToCreate; };

	private:
		void											DeleteFiles();
		void											InsertFiles();

		TAssetType								mAssetType;

		TFileSet									mFiles;

		TFileSet									mToCreate;
		TFileSet									mToDelete;
	};
}