#include "SFML_GLFW.h"

using namespace SFLW;

HWND SFLWwindow::initWin(GLFWwindow* window) {
	HWND hwin = glfwGetWin32Window(window);
	HINSTANCE Instance = (HINSTANCE)GetWindowLongPtr(hwin, GWLP_HINSTANCE);
	WNDCLASS wc;
	//DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
	int resx, resy;
	glfwGetWindowSize(window, &resx, &resy);
	wc.style = 0;
	wc.lpfnWndProc = &WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = Instance;
	wc.hIcon = NULL;
	wc.hCursor = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "SFML+GLFW app";
	RegisterClass(&wc);
	SetClassLongPtrA(hwin, GCLP_WNDPROC, (LONG_PTR)wc.lpfnWndProc);
	SetClassLongPtrA(hwin, GCLP_HBRBACKGROUND, (LONG_PTR)wc.hbrBackground);
	SetClassLongPtrA(hwin, GCLP_HMODULE, (LONG_PTR)wc.hInstance);
	SetClassLongPtrA(hwin, GCLP_MENUNAME, (LONG_PTR)wc.lpszMenuName);
	if (!setPixels(hwin))
	{
		return NULL;
	}
	/*HWND  View1 = CreateWindowA(wc.lpszClassName, NULL, Style, 0, 0, resx, resy, hwin, NULL, Instance, NULL);*/
	return hwin;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DWORD       tickCount;                              // Holds Current Tick Count
	__int64     timer;                                  // Used For The Tick Counter

	// Get The Window Context
	GLFWwindow* window = glfwGetCurrentContext();

	switch (uMsg)                                       // Evaluate Window Message
	{
	case WM_ERASEBKGND:                             // Check To See If Windows Is Trying To Erase The Background
		return 0;
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool SFLWwindow::setPixels(HWND hwin) {
	sf::RenderWindow proo(sf::VideoMode(1, 1), " ", sf::Style::None);
	HWND hw = proo.getSystemHandle();
	HDC hh = GetDC(hw);
	int act = GetPixelFormat(hh);
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormat = ChoosePixelFormat(hh, &pfd);
	memset(&pfd, 0, sizeof(pfd));
	DescribePixelFormat(hh, act, sizeof(pfd), &pfd);
	if (!SetPixelFormat(hh, act, &pfd)) {
		auto x = GetLastError();
		MessageBox(NULL, "Unable to set pixel format.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

void monitor_callback(GLFWmonitor* monitor, int event);

bool SFLWwindow::create(int resx, int resy, string name, int style, int mon, GLFWwindow* parent) {
	int posx, posy;
	switch (style)
	{
	case 1:
		if (!setupStyle(resx, resy, name, NULL, parent)) return false;
		posx = (monitors[mon].resx - resx) / 2;
		posy = (monitors[mon].resy - resy) / 2;
		SetWindowLongPtrA(Windentifier, GWL_STYLE, WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
		if (!SetWindowPos(Windentifier, HWND_TOPMOST, posx, posy, resx, resy, SWP_SHOWWINDOW | SWP_FRAMECHANGED)) return false;
		UpdateWindow(Windentifier);
		//glfwShowWindow(Gwindow);
		//glfwFocusWindow(Gwindow);
		show_button = true;
		buttons.initButtons(Swindow, Gwindow);
		return true;
		break;
	case 2:
		if (!setupStyle(resx, resy, name, NULL, parent)) return false;
		posx = (monitors[mon].resx - resx) / 2;
		posy = (monitors[mon].resy - resy) / 2;
		SetWindowLongPtrA(Windentifier, GWL_STYLE, WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
		if (!SetWindowPos(Windentifier, HWND_TOPMOST, posx, posy, resx, resy, SWP_SHOWWINDOW | SWP_FRAMECHANGED)) return false;
		UpdateWindow(Windentifier);
		//glfwShowWindow(Gwindow);
		//glfwFocusWindow(Gwindow);
		show_button = false;
		return true;
		break;
	case 3:
		if (!setupStyle(monitors[mon].resx, monitors[mon].resy, name, monitors[mon].monitor, NULL)) return false;
		UpdateWindow(Windentifier);
		glfwShowWindow(Gwindow);
		glfwFocusWindow(Gwindow);
		show_button = true;
		buttons.initButtons(Swindow, Gwindow);
		return true;
		break;
	case 4:
		if (!setupStyle(resx, resy, name, monitors[mon].monitor, NULL)) return false;
		UpdateWindow(Windentifier);
		glfwShowWindow(Gwindow);
		glfwFocusWindow(Gwindow);
		show_button = false;
		return true;
		break;
	case 5:
		glfwWindowHint(GLFW_RED_BITS, monitors[mon].mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, monitors[mon].mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, monitors[mon].mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, monitors[mon].mode->refreshRate);
		if (!setupStyle(monitors[mon].resx, monitors[mon].resy, name, monitors[mon].monitor, NULL)) return false;
		SetWindowLongPtrA(Windentifier, GWL_STYLE, WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
		if (!SetWindowPos(Windentifier, HWND_TOP, 0, 0, monitors[mon].resx, monitors[mon].resy, SWP_SHOWWINDOW | SWP_FRAMECHANGED)) return false;
		UpdateWindow(Windentifier);
		glfwShowWindow(Gwindow);
		glfwFocusWindow(Gwindow);
		show_button = true;
		buttons.initButtons(Swindow, Gwindow);
		return true;
		break;
	case 6:
		glfwWindowHint(GLFW_RED_BITS, monitors[mon].mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, monitors[mon].mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, monitors[mon].mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, monitors[mon].mode->refreshRate);
		if (!setupStyle(monitors[mon].resx, monitors[mon].resy, name, monitors[mon].monitor, NULL)) return false;
		SetWindowLongPtrA(Windentifier, GWL_STYLE, WS_POPUP | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
		if (!SetWindowPos(Windentifier, HWND_TOP, 0, 0, monitors[mon].resx, monitors[mon].resy, SWP_SHOWWINDOW | SWP_FRAMECHANGED)) return false;
		UpdateWindow(Windentifier);
		glfwShowWindow(Gwindow);
		glfwFocusWindow(Gwindow);
		show_button = false;
		return true;
		break;
	default:
		if (!setupStyle(resx, resy, name, NULL, parent)) return false;
		posx = abs(monitors[mon].resx - resx) / 2;
		posy = abs(monitors[mon].resy - resy) / 2;
		if (!SetWindowPos(Windentifier, HWND_TOPMOST, posx, posy, resx, resy, SWP_SHOWWINDOW | SWP_FRAMECHANGED)) return false;
		UpdateWindow(Windentifier);
		glfwShowWindow(Gwindow);
		glfwFocusWindow(Gwindow);
		show_button = false;
		return true;
		break;
	}
	return false;
}

bool SFLWwindow::setVsync(bool vsync) {
	Vsync = vsync;
	glfwSwapInterval(vsync);
	Swindow.setVerticalSyncEnabled(vsync);
	if (Swindow.isOpen())
	{
		return true;
	}
	Vsync = false;
	return false;
}

bool SFLWwindow::getVsyncState() {
	return Vsync;
}

void SFLWwindow::pollEvents() {
	if (show_button) {
		buttons.draw(Swindow, Gwindow);
	}
}

bool SFLWwindow::setupStyle(int resx, int resy, string name, GLFWmonitor* mon, GLFWwindow* parent) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_DEPTH_BITS, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_STENCIL_BITS, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	Gwindow = glfwCreateWindow(resx, resy, name.c_str(), mon, parent);
	if (parent == NULL)
	{
		glfwMakeContextCurrent(Gwindow);
		if (!GInit(Gwindow, Vsync)) {
			Log("Error initializing OpengGL");
			return false;
		}
	}
	glfwSetWindowSizeCallback(Gwindow, window_size_callback);
	Windentifier = initWin(Gwindow);
	if (Windentifier == nullptr)
	{
		Log("Error setting pixels");
		return false;
	}
	Swindow.create(Windentifier);
	//Swindow.setActive(true);
	sf::ContextSettings(24U, 8U, 0, 3U, 2U, 1, true);
	Swindow.setVerticalSyncEnabled(Vsync);
	view.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(Swindow.getSize())));
	Swindow.setView(view);
}

SFLWwindow::SFLWwindow() {
	monitors = GLdetectMonitors(GetSystemMetrics(SM_CMONITORS));
}