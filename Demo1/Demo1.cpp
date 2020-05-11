#include <Volt/Types.h>
#include <Volt/Module.h>

#include <iostream>

class CDemo1 final
	: public Volt::CModule
{
public:
	CDemo1() { std::cout << "Demo1 constructed" << std::endl; };
	~CDemo1() final { std::cout << "Demo1 destructed" << std::endl; };

	s32 OnUpdate() final
	{
		return true;
	}

	s32 OnRender() const final
	{
		return true;
	}
};

Volt::CModule* CreateModule() { return new CDemo1; }
void					 DestroyModule(Volt::CModule* ptr) { delete ptr; }