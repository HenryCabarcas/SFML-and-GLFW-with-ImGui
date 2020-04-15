#include "GLFW_Tools.h"

const char* GVersion() {
	// Setup window
	if (!glfwInit())
		return NULL;

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	return glsl_version;
}

bool GInit(GLFWwindow* window, bool vsync) {
	if (window == NULL)
		return false;
	glfwSwapInterval(vsync);
	glfwSetErrorCallback(glfw_error_callback);
	//glfwSetWindowSizeCallback(window, window_size_callback);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetWindowRefreshCallback(window, window_refresh_callback);
	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING)
	bool err = false;
	glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		Log("Failed to initialize OpenGL loader!");
		return false;
	}
	if (window == NULL)
	{
		Log("Error creating window");
		return false;
	}
	return true;
}

GLFWwindow* fullscreenW(const char* name, int x, int y, GLFWmonitor* monitor) {
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, name, monitor, NULL);
	return window;
}

GLFWwindow* fullscreenW(const char* name, int x, int y, GLFWmonitor* monitor, GLFWwindow* shwindow) {
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, name, monitor, shwindow);
	return window;
}

void GLMonitor::MonInit(int numDisplay, int op) {
	if (numDisplay == 1)
	{
		monitor = glfwGetPrimaryMonitor();
	}
	else {
		GLFWmonitor** tempM = glfwGetMonitors(&numDisplay);
		monitor = tempM[op];
	}
	glfwSetMonitorCallback(monitor_callback);
	mode = glfwGetVideoMode(monitor);
	const char* tem = glfwGetWin32Adapter(monitor);
	adapter = tem;
	const char* tem2 = glfwGetMonitorName(monitor);
	name = tem2;
	glfwGetMonitorPos(monitor, &startp[0], &startp[1]);
	resx = mode->width;
	resy = mode->height;
	state = true;
}

vector<GLMonitor> GLdetectMonitors(int numDisplay) {
	vector<GLMonitor> tempp;
	GLMonitor t;
	if (numDisplay == 1)
	{
		t.MonInit(numDisplay, 0);
		tempp.push_back(t);
	}
	else {
		for (int i = 0; i < numDisplay; i++)
		{
			t.MonInit(numDisplay, i);
			tempp.push_back(t);
		}
	}
	return tempp;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

void monitor_callback(GLFWmonitor* monitor, int event)
{
	if (event == GLFW_CONNECTED)
	{
		// The monitor was connected
	}
	else if (event == GLFW_DISCONNECTED)
	{
		Log("Monitor disconnected");
	}
}

static void glfw_error_callback(int error, const char* description)
{
	string err = "Glfw Error " + to_string(error) + description;
	Log(err);
}

void window_refresh_callback(GLFWwindow* window) {
	glfwSwapBuffers(window);
}