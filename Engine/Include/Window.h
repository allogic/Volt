#pragma once

#include <Core.h>

namespace Volt
{
	class CWindow final
	{
	public:
		CWindow(const s32 width, const s32 height, const s32 antialiasing, const s32 vsync);
		~CWindow();

		inline GLFWwindow* Ptr() const { return mpWindow; }

	private:
		GLFWwindow* mpWindow = nullptr;
	};
}