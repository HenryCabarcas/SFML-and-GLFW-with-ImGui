#pragma once
// Windows
#include <iostream>
#include <stdio.h>
#include <comdef.h>
#include <windows.h>
#include <WinUser.h>
#include <winuser.inl>
#include <vector>

// imGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "imgui-sfml/imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>
//#include <GL/GL.h>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING)
#define GLFW_INCLUDE_NONE         // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>  // Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#define GLFW_EXPOSE_NATIVE_WIN32 0
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "wingdi.h"
#include <GL/GL.h>
#include <GL/glcorearb.h>
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#define min(a,b) (((a) < (b)) ? (a) : (b))

using namespace ImGui;
using namespace std;

static const auto PI = acos(-1);
static const int cores = 4;
