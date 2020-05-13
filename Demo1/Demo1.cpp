#include <Volt.h>

#include <iostream>

class CDemo1
	: public Volt::CModule
{
public:
	CDemo1() { std::cout << "Demo1 constructed" << std::endl; };
	virtual ~CDemo1() { std::cout << "Demo1 destructed" << std::endl; };

	inline const std::string Id() const { return "Demo1"; };

	s32 OnUpdate() override
	{
		//std::cout << "Hello from demo1" << std::endl;

		return 0;
	}

	s32 OnRender() const override
	{
		return 0;
	}
};

MAKE_MODULE(CDemo1);