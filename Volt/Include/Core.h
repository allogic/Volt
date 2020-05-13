#pragma once

#define VOLT_OBSERVED_PATH "C:\\Users\\burmi\\Downloads\\Volt\\x64\\Debug"
#define VOLT_ASSET_PATH "C:\\Users\\burmi\\Downloads\\Volt\\x64\\Debug\\Assets"

#define _AMD64_

#ifdef VOLT_ENGINE_WINDOWS_ENTRY
	#include <Windows.h>
#else
	#ifndef VOLT_WINMINDEF
		#define VOLT_WINMINDEF
		#include <minwindef.h>
	#endif
	#ifndef VOLT_LIBLOADERAPI
		#define VOLT_LIBLOADERAPI
		#include <libloaderapi.h>
	#endif
#endif

#include <Glad/glad.h>
#include <Glfw/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <thread>
#include <memory>
#include <utility>
#include <algorithm>
#include <type_traits>

#define VOLT_API __declspec(dllexport)

#ifndef VOLT_GL_MAJOR
	#define VOLT_GL_MAJOR 4
#endif

#ifndef VOLT_GL_MINOR
	#define VOLT_GL_MINOR 0
#endif

#define VOLT_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;
#define VOLT_EXIT { std::exit(EXIT_FAILURE); }
#define VOLT_ASSERT(EXPR, MSG) { if (!(EXPR)) { VOLT_TRACE(MSG); VOLT_EXIT; } }