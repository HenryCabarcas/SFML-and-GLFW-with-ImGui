#pragma once
#include "Dependances.h"
#include "Tools.h"

static sf::Mouse mouse;
static sf::Vector2i mousepos;
static sf::Vector2u windowsize;
static sf::Vector2i mousepos_g;
namespace sftool {
	class WinButtons
	{
	public:
		WinButtons();
		~WinButtons();
		sf::Texture normal;
		sf::Texture maxi;
		sf::Texture mini;
		sf::Texture closed;
		sf::Sprite snormal;
		sf::Sprite smaxi;
		sf::Sprite smini;
		sf::Sprite sclosed;
		sf::Vector2i mpos;
		sf::Vector2u wpos;
		sf::Vector2i mpos_g;
		sf::Mouse mouse;
		sf::Vector2f globalpos;
		string filenames[4] = {
			"Resources/Normal.png",
			"Resources/Max.png",
			"Resources/Min.png",
			"Resources/Close.png" };
		bool nodraw = true;
		int active = 0;
		int ms = 0;
		bool show = false;
		bool ism = false;
		int pms = 0;
		bool action(sf::RenderWindow& window, GLFWwindow* window2);
		bool showbuttons();
		void getparams(sf::RenderWindow& window);
		bool initButtons(sf::RenderWindow& window, GLFWwindow* window2);
		void draw(sf::RenderWindow& window, GLFWwindow* window2);
	};

	class sfmlImage
	{
	public:
		sfmlImage() {}
		sf::Texture texture;
		sf::Sprite sprite;
#ifdef WINAPI
		HBITMAP bmp = NULL;
#endif // WINAPI
	};
}
void resizewithmouse(sf::RenderWindow& window);
