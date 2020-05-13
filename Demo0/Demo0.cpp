#include <Volt.h>

#include <iostream>

class CDemo0
	: public Volt::CModule
{
public:
	CDemo0() { std::cout << "Demo0 constructed" << std::endl; };
	virtual ~CDemo0() { std::cout << "Demo0 destructed" << std::endl; };

	inline const std::string Id() const { return "Demo0"; };

	s32 OnUpdate() override
	{
		//std::cout << "Hello from demo0" << std::endl;

		return 1;
	}

	s32 OnRender() const override
	{
		return 0;
	}
};

MAKE_MODULE(CDemo0);