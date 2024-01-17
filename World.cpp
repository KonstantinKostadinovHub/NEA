#include "World.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "imgui/implot.h"

#include <string>

std::shared_ptr<sf::RenderWindow> World::m_window = nullptr;
SCENE World::m_state = SCENE::MENU;
sf::Clock World::m_runClock = sf::Clock();

World::World()
{
}

World::~World()
{
}

void World::init()
{
	m_window.reset(new sf::RenderWindow(sf::VideoMode(1920, 1080), "Window Title", sf::Style::Fullscreen, sf::ContextSettings()));
	ImGui::SFML::Init(*m_window);
	ImGui::CreateContext();
	ImPlot::CreateContext();
	
	// Must be initialised after we have created the window
	m_game.Init();
	m_menu.Init();
	m_input = Input::GetInstance();
	m_input.Init(m_window);

	m_runClock.restart();
}

void World::run()
{
	float passed = deltaClock.getElapsedTime().asMilliseconds();

	ImGui::SFML::Update(*m_window, deltaClock.restart());
	m_window->clear(sf::Color(33, 30, 41));
	m_input.Update();
	
	if (m_state == SCENE::MENU) {
		m_menu.Run();
	}
	else if (m_state == SCENE::PLAYGROUND) {
		m_game.Run();
	}
	
	ShowFPS(passed);
	ImGui::SFML::Render(*m_window);
	m_window->display();

}

int World::GetTimeInMs()
{
	return m_runClock.getElapsedTime().asMilliseconds();
}

void World::ShowFPS(float passed)
{
	ImGui::SetNextWindowPos(ImVec2(1750, 1055));

	ImGui::Begin("FPS", NULL, DEFAULT_WINDOW);
	
	std::string fps = "FPS: " + std::to_string(int(1000 / passed));
	ImGui::Text(fps.c_str());

	ImGui::End();
}
