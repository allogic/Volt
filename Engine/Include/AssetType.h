#pragma once

#include <Core.h>

namespace Volt
{
	struct TAssetType
	{
		enum : u32
		{
			Module = 0,
		} type;

		std::filesystem::path folder;
		std::string extension;
	};
}