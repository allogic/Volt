#include <Volt.h>

#include <iostream>

class CDemo1
	: public Volt::CModule
{
public:
	CDemo1(const char* id) : Volt::CModule(id) { std::cout << "Demo0 constructed" << std::endl; };
	virtual ~CDemo1() { std::cout << "Demo0 destructed" << std::endl; };

	s32 OnUpdate() override
	{
		return 0;
	}

	s32 OnRender() const override
	{
		return 0;
	}
};

MAKE_MODULE(CDemo1, "Demo1");