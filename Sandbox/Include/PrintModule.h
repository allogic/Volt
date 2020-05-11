#pragma once

#include <Volt/Module.h>

namespace Sandbox
{
	class PrintModule final
		: public Volt::Module
	{
		PrintModule() = default;
		~PrintModule() = default;

		int OnUpdate() final
		{

		}

		int OnRender() const final
		{

		}
	};
}