#include "SFML_Tools.h"
using namespace sftool;

void resizewithmouse(sf::RenderWindow& window) {
	mousepos = mouse.getPosition(window);
	windowsize = window.getSize();
	mousepos_g = mouse.getPosition();
	int comx = abs(INT(windowsize.x - mousepos.x));
	int comy = abs(INT(windowsize.y - mousepos.y));
	if (comx <= 15 && mouse.isButtonPressed(sf::Mouse::Left))
	{
		window.setSize(sf::Vector2u(mouse.getPosition(window).x, windowsize.y));
	}
	else if (comy <= 15 && mouse.isButtonPressed(sf::Mouse::Left))
	{
		window.setSize(sf::Vector2u(windowsize.x, mouse.getPosition(window).y));
	}
}

WinButtons::WinButtons()
{
	normal.loadFromFile(filenames[0]);
	maxi.loadFromFile(filenames[1]);
	mini.loadFromFile(filenames[2]);
	closed.loadFromFile(filenames[3]);
	normal.setSmooth(true);
	maxi.setSmooth(true);
	mini.setSmooth(true);
	closed.setSmooth(true);
	snormal.setTexture(normal);
	smaxi.setTexture(maxi);
	smini.setTexture(mini);
	sclosed.setTexture(closed);
}

WinButtons::~WinButtons()
{
}

bool WinButtons::action(sf::RenderWindow& window, GLFWwindow* window2) {
	if (showbuttons()) {
		switch (active)
		{
		case 1:
			if (!ism)
			{
				glfwMaximizeWindow(window2);
				//ShowWindow(window.getSystemHandle(), SW_SHOWMAXIMIZED);
				ism = true;
				return true;
			}
			else
			{
				glfwRestoreWindow(window2);
				//ShowWindow(window.getSystemHandle(), SW_RESTORE);
				ism = false;
				return true;
			}

			break;
		case 2:
			glfwIconifyWindow(window2);
			//ShowWindow(window.getSystemHandle(), SW_MINIMIZE);
			return true;
			break;
		case 3:
			window.close();
			return true;
			break;
		default:
			return false;
			break;
		}
	}
	return true;
}

void WinButtons::getparams(sf::RenderWindow& window) {
	mpos = mouse.getPosition(window);
	int x, y;
	//glfwGetWindowSize(window2, &x, &y);
	wpos = window.getSize();//sf::Vector2u(x, y);
	//mpos_g = mouse.getPosition();
	globalpos.x = wpos.x - 110;
}

bool WinButtons::showbuttons() {
	int actx = abs(INT(mpos.x - wpos.x));
	int acty = abs(INT(mpos.y - wpos.y));

	if (mpos.y <= 30 && actx <= 110 && actx > 10)
	{
		if (actx > 10 && actx <= 50)
		{
			active = 3;
		}
		else if (actx > 50 && actx <= 80)
		{
			active = 1;
		}
		else if (actx > 80 && actx <= 110)
		{
			active = 2;
		}
		ms++;
		if (ms > 150) {
			show = true;
			ms = 0;
		}
		if (show)
		{
			if (globalpos.y < 0)
			{
				globalpos.y = globalpos.y + 0.5f;
			}
		}
		switch (active)
		{
		case 1:
			smaxi.setPosition(globalpos);
			if (mouse.isButtonPressed(sf::Mouse::Left))
			{
				return true;
			}
			break;
		case 2:
			smini.setPosition(globalpos);
			if (mouse.isButtonPressed(sf::Mouse::Left))
			{
				return true;
			}
			break;
		case 3:
			sclosed.setPosition(globalpos);
			if (mouse.isButtonPressed(sf::Mouse::Left))
			{
				return true;
			}
			break;
		default:
			snormal.setPosition(globalpos);
			break;
		}
		return false;
	}
	else if (globalpos.y + 30 > 0)
	{
		active = 0;
		show = false;
		for (size_t i = 0; i < 300; i++)
		{
			if (snormal.getPosition().y <= -30)
			{
				break;
			}
			globalpos.y = globalpos.y - 0.005f;
			snormal.setPosition(globalpos);
		}
		smini.setPosition(globalpos);
		smaxi.setPosition(globalpos);
		sclosed.setPosition(globalpos);
	}
	return false;
}

bool WinButtons::initButtons(sf::RenderWindow& window, GLFWwindow* window2) {
	getparams(window);
	globalpos.y = -30.f;
	snormal.setPosition(globalpos);
	smaxi.setPosition(globalpos);
	smini.setPosition(globalpos);
	sclosed.setPosition(globalpos);
	if (snormal.getPosition() == sf::Vector2f(wpos.x - 110, -30))
	{
		return true;
	}

	return false;
}

void WinButtons::draw(sf::RenderWindow& window, GLFWwindow* window2) {
	getparams(window);
	action(window, window2);
	switch (active)
	{
	case 0:
		snormal.setPosition(globalpos);
		window.draw(snormal);
		break;
	case 1:
		smaxi.setPosition(globalpos);
		window.draw(smaxi);
		break;
	case 2:
		smini.setPosition(globalpos);
		window.draw(smini);
		break;
	default:
		sclosed.setPosition(globalpos);
		window.draw(sclosed);
		break;
	}
}

void ReshapeGL(int width, int height)                              // Reshape The Window When It's Moved Or Resized
{
	glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));                 // Reset The Current Viewport
}