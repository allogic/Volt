#define VOLT_ENGINE_WINDOWS_ENTRY

#include <Core.h>
#include <AssetDatabase.h>

int main()
{
  glfwSetErrorCallback([](s32 error, const char* msg) { VOLT_TRACE(msg); });

  if (!glfwInit())
  {
    VOLT_TRACE("Failed initializing glfw");
    VOLT_EXIT;
  }

  auto& assetDb = Volt::CAssetDatabase::Instance();

  assetDb.UpdateModules();

  f32 time = 0.f;
  f32 prevTime = 0.f;
  f32 deltaTime = 0.f;

  const f32 renderRate = 1.f / 60.f;
  f32 prevRenderTime = 0.f;

  const f32 watchRate = 1.f / 1.f;
  f32 prevWatchTime = 0.f;

  s32 status = 0;
  s32 glLoaded = 0;

  while (!status)
  {
    time = static_cast<f32>(glfwGetTime());
    deltaTime = time - prevTime;

    for (const auto& moduleInfo : assetDb.Modules())
    {
      glfwMakeContextCurrent(moduleInfo.pWindow);
      glfwSwapInterval(0);
      
      if (!glLoaded)
      {
        glLoaded = 1;
      
        if (!gladLoadGL())
        {
          VOLT_TRACE("Failed loading gl");
          VOLT_EXIT;
        }
      }
    
      status = moduleInfo.pModule->OnUpdate();
    }

    if ((time - prevRenderTime) >= renderRate)
    {
      for (const auto& moduleInfo : assetDb.Modules())
      {
        status = moduleInfo.pModule->OnRender();

        glfwSwapBuffers(moduleInfo.pWindow);
      }

      prevRenderTime = time;
    }

    if ((time - prevWatchTime) >= watchRate)
    {
      assetDb.UpdateModules();

      if (glLoaded)
      {
        assetDb.UpdateShaders();
      }

      prevWatchTime = time;
    }

    glfwPollEvents();

    prevTime = time;
  }

  Volt::CAssetDatabase::Delete();

  glfwTerminate();

  return 0;
}