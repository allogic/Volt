#pragma once

#define VOLT_OBSERVED_PATH "C:\\Users\\Michael\\Downloads\\Volt\\x64\\Debug"
#define VOLT_ASSET_PATH "C:\\Users\\Michael\\Downloads\\Volt\\x64\\Debug\\Assets"

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
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <memory>
#include <thread>
#include <utility>
#include <algorithm>
#include <type_traits>
#include <chrono>

#define VOLT_API __declspec(dllexport)

#ifndef VOLT_GL_MAJOR
  #define VOLT_GL_MAJOR 4
#endif

#ifndef VOLT_GL_MINOR
  #define VOLT_GL_MINOR 6
#endif

#define VOLT_TRACE(MSG) { std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl; }
#define VOLT_EXIT { std::exit(EXIT_FAILURE); }
#define VOLT_ASSERT(EXPR, MSG) { if (!(EXPR)) { VOLT_TRACE(MSG); VOLT_EXIT; } }

#define VOLT_DECLARE_ITERABLE(VALUE)                     \
inline auto begin() { return std::begin(VALUE); }        \
inline auto end() { return std::end(VALUE); }            \
                                                         \
inline auto begin() const { return std::begin(VALUE); }  \
inline auto end() const { return std::end(VALUE); }

#define VOLT_MAKE_MODULE(TYPE)                                     \
Volt::CModule*  CreateModule() { return new TYPE; }                \
void            DestroyModule(Volt::CModule* ptr) { delete ptr; }