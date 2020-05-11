#include <Volt/Types.h>
#include <Volt/Module.h>

#include <iostream>

class CDemo0 final
	: public Volt::CModule
{
public:
	CDemo0() { std::cout << "Demo0 constructed" << std::endl; };
	~CDemo0() final { std::cout << "Demo0 destructed" << std::endl; };

	s32 OnUpdate() final
	{
		return true;
	}

	s32 OnRender() const final
	{
		return true;
	}
};

Volt::CModule* CreateModule() { return new CDemo0; }
void					 DestroyModule(Volt::CModule* ptr) { delete ptr; }