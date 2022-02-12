#pragma once
#include "GLFW_Tools.h"
#include "SFML_Tools.h"
namespace SFLW {
	constexpr int SDefault = 0;
	constexpr int SNoBorder = 1;
	constexpr int SNoBorder_withoutbuttons = 2;
	constexpr int SFullScreen = 3;
	constexpr int SFullScreen_withoutbuttons = 4;
	constexpr int SWindowedFullScreen = 5;
	constexpr int SWindowedFullScreen_nobutton = 6;
	class SFLWwindow
	{
	public:
		sf::RenderWindow Swindow;
		sf::View view;
		sftool::WinButtons buttons;
		GLFWwindow* Gwindow;
		HWND Windentifier;
		vector<GLMonitor> monitors;
		bool Vsync = false;
		bool show_button = false;
		int monitorcount = 1;
		bool create(int resx, int resy, string name, int style, int mon, GLFWwindow* parent);
		bool create(int resx, int resy, string name, int style, int mon) {
			create(resx, resy, name, style, mon, NULL);
			return true;
		}
		bool create(int resx, int resy, string name, int style) {
			create(resx, resy, name, style, NULL, NULL);
			return true;
		}
		bool create(int resx, int resy, string name) {
			create(resx, resy, name, 0, NULL, NULL);
			return true;
		}

		bool setVsync(bool vsync);
		bool getVsyncState();
		void pollEvents();
		SFLWwindow();
		//~SFLWwindow();

	private:
		HWND initWin(GLFWwindow* window);
		bool setPixels(HWND hwin);
		bool setupStyle(int resx, int resy, string name, GLFWmonitor* mon, GLFWwindow* parent);
	};
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);