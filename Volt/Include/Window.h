#pragma once

#include <Core.h>
#include <Types.h>

namespace Volt
{
	class CWindow
	{
	public:
		CWindow(const s32 width, const s32 height, const s32 antialiasing, const s32 vsync);
		virtual ~CWindow();

		inline GLFWwindow* GlfwWindowPtr() const { return mpGlfwWindow; }

	private:
		GLFWwindow* mpGlfwWindow = nullptr;
	};
}