#include <Volt.h>

#include <iostream>

class CGame
	: public Volt::CModule
{
public:
	CGame()
	{
		//mpWindow = new Volt::CWindow(1280, 720, 0, 0);
		std::cout << "Game window ptr: " << mpWindow << std::endl;
	};
	virtual ~CGame()
	{
		//delete mpWindow;
	};

	inline const std::string Id() const { return "Game"; };

	s32 OnUpdate() override
	{
		return 0;
	}

	s32 OnRender() const override
	{
		return 0;
	}

	Volt::CWindow* mpWindow;
};

MAKE_MODULE(CGame);