#pragma once
#include "Dependances.h"
#include "Tools.h"
//
class glfwImage
{
public:
	glfwImage() { glGenTextures(1, &texture); }
	GLuint texture = 0;
#ifdef WINAPI
	HBITMAP bmp = NULL;
#endif // WINAPI
};

class GLMonitor
{
public:
	GLFWmonitor* monitor = NULL;
	const GLFWvidmode* mode;
	int startp[2];
	int resx, resy;
	std::string adapter;
	std::string name;
	bool state = false;
	void MonInit(int numDisplay, int op);

private:
};

static void glfw_error_callback(int error, const char* description);
const char* GVersion();
bool GInit(GLFWwindow* window, bool vsync);
GLFWwindow* fullscreenW(const char* name, int x, int y, GLFWmonitor* monitor, GLFWwindow* shwindow);
GLFWwindow* fullscreenW(const char* name, int x, int y, GLFWmonitor* monitor);
void monitor_callback(GLFWmonitor* monitor, int event);
vector<GLMonitor> GLdetectMonitors(int numDisplay);
void window_size_callback(GLFWwindow* window, int width, int height);
