#include <Window.h>

Volt::CWindow::CWindow(const s32 width, const s32 height, const s32 antialiasing, const s32 vsync)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VOLT_GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VOLT_GL_MINOR);
	glfwWindowHint(GLFW_SAMPLES, antialiasing);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mpGlfwWindow = glfwCreateWindow(width, height, "", nullptr, nullptr);

	//if (!mpGlfwWindow)
	//{
	//	VOLT_TRACE("Failed creating glfw window");
	//
	//	return;
	//}

	glfwMakeContextCurrent(mpGlfwWindow);
	glfwSwapInterval(vsync);

	//glfwSetWindowUserPointer(mpWindow, pApplication);

	glfwSetWindowCloseCallback(mpGlfwWindow, [](GLFWwindow* pWindow) {
		//auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));
		//
		//app->mRunning = false;
		});
	glfwSetWindowSizeCallback(mpGlfwWindow, [](GLFWwindow* pWindow, s32 w, s32 h) {
		//auto* app = reinterpret_cast<CApplication*>(glfwGetWindowUserPointer(pWindow));
		//
		//app->mWindowConfig.width = width;
		//app->mWindowConfig.height = height;
		});
}

Volt::CWindow::~CWindow()
{
	if (mpGlfwWindow)
		glfwDestroyWindow(mpGlfwWindow);
}