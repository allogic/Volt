#include <Volt.h>

#include <iostream>

class CEditor
	: public Volt::CModule
{
public:
	CEditor()
	{
		mpWindow = new Volt::CWindow(1280, 720, 0, 0);
		std::cout << "Created engine window ptr: " << mpWindow << std::endl;
	};
	virtual ~CEditor()
	{
		delete mpWindow;
		std::cout << "Destroyed engine window ptr: " << mpWindow << std::endl;
	};

	inline const std::string Id() const { return "Editor"; };

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

MAKE_MODULE(CEditor);