#include <Core.h>
#include <AssetDatabase.h>
#include <Window.h>

int main()
{
	auto& assetDb = Volt::CAssetDatabase::Get("C:\\Users\\Michael\\source\\repos\\Volt\\x64\\Debug\\Streaming");
	
	assetDb.RegisterAssetType({ Volt::TAssetType::Module, "C:\\Users\\Michael\\source\\repos\\Volt\\x64\\Debug", ".dll" });

	Volt::CWindow window(1280, 720, 0, 0);

	f32 time = 0.f;
	f32 prevTime = 0.f;
	f32 deltaTime = 0.f;

	const f32 renderRate = 1.f / 60.f;
	f32 prevRenderTime = 0.f;

	const f32 watchRate = 1.f / 1.f;
	f32 prevWatchTime = 0.f;

	while (true)
	{
		glfwPollEvents();

		time = static_cast<f32>(glfwGetTime());
		deltaTime = time - prevTime;

		if ((time - prevRenderTime) >= renderRate)
		{
			glfwSwapBuffers(window.Ptr());

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