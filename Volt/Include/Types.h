#pragma once

#include <Core.h>

using s32 = int;
using u32 = int unsigned;

using f32 = float;
using d32 = double;

namespace Volt
{
	using TPathSet = std::set<std::filesystem::path>;

	struct TModuleInfo;

	enum TAssetType : u32
	{
		Module = 0,
	};
}