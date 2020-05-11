#pragma once

namespace Volt
{
	class CModule
	{
	public:
		using CreateModule = CModule * (*)();
		using DestroyModule = void (*)(CModule*);

		CModule() = default;
		virtual ~CModule() = default;

		virtual s32 OnUpdate() { return true; };
		virtual s32 OnRender() const { return true; };
	};
}

extern "C"
{
	__declspec(dllexport) Volt::CModule* CreateModule();
	__declspec(dllexport) void					 DestroyModule(Volt::CModule* ptr);
}