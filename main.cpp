#include "SFML_GLFW.h"
#include <gl/GL.h>

int main(int, char**)
{
	int sizex = 500, sizey = 100;
	bool is_win2 = false;
	char windowTitle[255] = "ImGui + SFML = <3";
	float color[3] = { 0.f, 0.f, 0.f };
	const char* glsl_version = GVersion();
	sf::Texture tex;
	tex.loadFromFile("Resources/Normal.png");
	sf::Sprite sp;
	sp.setTexture(tex);
	sf::Clock deltaClock;
	sf::Clock deltaClock2;
	sf::Color bgColor;
	SFLW::SFLWwindow win;
	SFLW::SFLWwindow win2;
	if (!win.create(sizex, sizey, "hi", SFLW::SDefault)) {
		return 1;
	}
	ImGui_ImplOpenGL3_Init(glsl_version);
	win.setVsync(false);
	win.Swindow.setTitle(windowTitle);

	ImGui::SFML::Init(win.Swindow);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(win.Gwindow, true);

	while (win.Swindow.isOpen()) {
		glfwPollEvents();
		sf::Event event;
		while (win.Swindow.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				win.Swindow.close();
			}
			if (event.type == sf::Event::Resized)
			{
				win.view.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(win.Swindow.getSize())));
				win.Swindow.setView(win.view);
				glViewport(0, 0, win.Swindow.getSize().x, win.Swindow.getSize().y);
				//win.Swindow.display();
				//glfwSwapBuffers(win.Gwindow);
				/*if (deltaClock.getElapsedTime().asMilliseconds() > 500)
				{
				}*/
			}
			if (event.type == sf::Event::MouseLeft)
			{
			}
		}
		//}

		ImGui::SFML::Update(win.Swindow, deltaClock.restart());
		//ImGui::SetCurrentContext()
		resizewithmouse(win.Swindow);
		ImGui::Begin("Sample window"); // begin window
		   // Background color edit
		if (ImGui::ColorEdit3("Background color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", windowTitle, 255);

		if (ImGui::Button("Update window title")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			win.Swindow.setTitle(windowTitle);
		}
		if (ImGui::Button("Create Window"))
		{
			win2.create(500, 300, "Window2", SFLW::SNoBorder, NULL, win.Gwindow);
			ImGui::SFML::Init(win2.Swindow);
			ImGui_ImplGlfw_InitForOpenGL(win2.Gwindow, true);
			is_win2 = true;
		}
		ImGui::Text("%.1ffps", GetIO().Framerate);
		ImGui::End(); // end window
		//glfwGetFramebufferSize(win.Gwindow, (INT*)win.Swindow.getSize().x, (INT*)win.Swindow.getSize().y);
		//glViewport(0, 0, win.Swindow.getSize().x, 30);

		glViewport(0, 30, win.Swindow.getSize().x, win.Swindow.getSize().y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		win.Swindow.clear(bgColor); // fill background with color
		//win.pollEvents();
		ImGui::SFML::Render(win.Swindow);
		win.Swindow.draw(sp);
		win.Swindow.display();

		if (is_win2)
		{
			glfwMakeContextCurrent(win2.Gwindow);
			glfwPollEvents();
			sf::Event event2;
			while (win2.Swindow.pollEvent(event2)) {
				ImGui::SFML::ProcessEvent(event2);
				if (event2.type == sf::Event::Closed)
				{
					glfwSwapBuffers(win.Gwindow);
					win2.Swindow.close();

					is_win2 = false;
					//goto win2off;
				}
				if (event2.type == sf::Event::Resized)
				{
					win2.view.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(win2.Swindow.getSize())));
					win2.Swindow.setView(win2.view);
					glfwSwapBuffers(win2.Gwindow);
				}
			}
			ImGui::SFML::Update(win2.Swindow, deltaClock2.restart());
			ImGui::SetNextWindowSize(ImVec2(250, 150));
			ImGui::Begin(windowTitle);
			ImGui::Text("HIIIIIIII");
			ImGui::End();
			//ImGui::Render();
			glViewport(0, 0, win2.Swindow.getSize().x, win2.Swindow.getSize().y);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			win2.Swindow.clear(bgColor); // fill background with color
			ImGui::SFML::Render(win2.Swindow);
			win2.Swindow.display();
			glfwMakeContextCurrent(win.Gwindow);
			//glfwSwapBuffers(win2.Gwindow);
		//win2off:
			//glfwMakeContextCurrent(win.Gwindow);
		}
	}

	ImGui::SFML::Shutdown();
	UnregisterClass("SFML+GLFW app", nullptr);
	return 0;
}