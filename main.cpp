#include "SFML_GLFW.h"
#include <gl/GL.h>

int main(int, char**)
{
	int sizex = 800, sizey = 600;
	bool is_win2 = false;
	char windowTitle[255] = "50M Simulation";
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
	if (!win.create(sizex, sizey, "hi", SFLW::SNoBorder)) {
		return 1;
	}
	win.setVsync(false);
	win.Swindow.setTitle(windowTitle);
	ImGui::SFML::Init(win.Swindow);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(win.Gwindow, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

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

	}

	ImGui::SFML::Shutdown();
	UnregisterClass("SFML+GLFW app", nullptr);
	return 0;
}