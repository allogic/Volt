#pragma once

#include <Types.h>
#include <Core.h>

namespace Volt
{
	class CModule
	{
	public:
		using CreateModule = CModule* (*)();
		using DestroyModule = void (*)(CModule*);

		CModule(const char* id) {};
		virtual ~CModule() = default;

		virtual s32 OnUpdate() { return 0; };
		virtual s32 OnRender() const { return 0; };
	};
}

extern "C"
{
	VOLT_API Volt::CModule* CreateModule();
	VOLT_API Volt::CModule* DestroyModule();
}

#define MAKE_MODULE(TYPE, ID)																			\
Volt::CModule*	CreateModule() { return new TYPE(ID); }						\
void						DestroyModule(Volt::CModule* ptr) { delete ptr; }