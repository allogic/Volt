#pragma once

#include <Core.h>
#include <Types.h>

namespace Volt
{
	class CModule
	{
	public:
		using CreateModule = CModule* (*)();
		using DestroyModule = void (*)(CModule*);

		CModule() = default;
		virtual ~CModule() = default;

		virtual s32												OnUpdate() { return 0; };
		virtual s32												OnRender() const { return 0; };

		inline virtual const char*				WindowTitle() const = 0;
		inline virtual const s32					WindowWidth() const = 0;
		inline virtual const s32					WindowHeight() const = 0;
	};
}

extern "C"
{
	VOLT_API Volt::CModule* CreateModule();
	VOLT_API void						DestroyModule(Volt::CModule* ptr);
}

#define MAKE_MODULE(TYPE)																					\
Volt::CModule*	CreateModule() { return new TYPE(); }							\
void						DestroyModule(Volt::CModule* ptr) { delete ptr; }