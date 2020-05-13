#define VOLT_ENGINE_WINDOWS_ENTRY

#include <Core.h>
#include <AssetDatabase.h>
#include <Window.h>

int main()
{
	auto& assetDb = Volt::CAssetDatabase::Instance();

	Volt::CWindow window(1280, 720, 0, 0);

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
		glfwPollEvents();

		time = static_cast<f32>(glfwGetTime());
		deltaTime = time - prevTime;

		for (Volt::CModule* pModule : assetDb.Modules())
			status = pModule->OnUpdate();


		if ((time - prevRenderTime) >= renderRate)
		{
			for (Volt::CModule* pModule : assetDb.Modules())
				status = pModule->OnRender();

			glfwSwapBuffers(window.GlfwWindowPtr());

			prevRenderTime = time;
		}

		if ((time - prevWatchTime) >= watchRate)
		{
			assetDb.Update();

			prevWatchTime = time;
		}

		prevTime = time;
	}

	Volt::CAssetDatabase::Delete();

	return 0;
}