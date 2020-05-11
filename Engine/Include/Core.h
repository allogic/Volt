#pragma once

#include <Windows.h>

#include <Glad/glad.h>

#include <Volt/Volt.h>

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

#include <Glfw/glfw3.h>

#define VOLT_API_INTERN
#define VOLT_API_EXTERN __declspec(dllexport)

#ifndef VOLT_GL_MAJOR
	#define VOLT_GL_MAJOR 4
#endif

#ifndef VOLT_GL_MINOR
	#define VOLT_GL_MINOR 0
#endif

#define VOLT_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;