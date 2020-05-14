#define VOLT_ENGINE_WINDOWS_ENTRY

#include <Core.h>
#include <AssetDatabase.h>

int main()
{
	glfwSetErrorCallback([](s32 error, const char* msg) {	VOLT_TRACE(msg); });

	if (!glfwInit())
	{
		VOLT_TRACE("Failed initializing glfw");
		VOLT_EXIT;
	}

	auto& assetDb = Volt::CAssetDatabase::Instance();

	assetDb.Update();

	f32 time = 0.f;
	f32 prevTime = 0.f;
	f32 deltaTime = 0.f;

	const f32 renderRate = 1.f / 60.f;
	f32 prevRenderTime = 0.f;

	const f32 watchRate = 1.f / 1.f;
	f32 prevWatchTime = 0.f;

	s32 status = 0;

	while (!status)
	{
		time = static_cast<f32>(glfwGetTime());
		deltaTime = time - prevTime;

		for (auto& module : assetDb.Modules())
		{
			glfwMakeContextCurrent(module.pWindow);
			glfwSwapInterval(0);

			//static s32 glLoaded = 0; // check if only once gladLoadGL()
			//
			//if (!glLoaded)
			//{
			//	glLoaded = 1;
			//
			//	if (!gladLoadGL())
			//	{
			//		VOLT_TRACE("Failed loading gl");
			//		VOLT_EXIT;
			//	}
			//}

			status = module.pModule->OnUpdate();


		}

		if ((time - prevRenderTime) >= renderRate)
		{
			for (Volt::CModule* pModule : assetDb.Modules())
				status = pModule->OnRender();

			//glfwSwapBuffers(window.GlfwWindowPtr());

			prevRenderTime = time;
		}

		if ((time - prevWatchTime) >= watchRate)
		{
			assetDb.Update();

			prevWatchTime = time;
		}

		glfwPollEvents();

		prevTime = time;
	}

	Volt::CAssetDatabase::Delete();

	glfwTerminate();

	return 0;
}