#include "World.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <string>

std::shared_ptr<sf::RenderWindow> World::m_window = nullptr;
SCENE World::m_state = SCENE::MENU;
bool World::isLeftClicked = false;
bool World::isLeftPressed = false;

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
	
	// Must be initialised after we have created the window
	m_game.Init();
	m_menu.Init();
	m_input = Input::GetInstance();
	m_input.Init(m_window);
}

void World::run()
{
	float passed = deltaClock.getElapsedTime().asMilliseconds();
	//std::cout << int(1000 / passed) << " FPS \n";
	deltaClock.restart();

	m_window->clear(sf::Color(18, 33, 43));
	m_input.Update();
	ImGui::SFML::Update(*m_window, deltaClock.restart());
	
	if (m_state == SCENE::MENU) {
		m_menu.Run();
	}
	else if (m_state == SCENE::PLAYGROUND) {
		m_game.Run();
	}
	
	ImGui::SFML::Render(*m_window);
	m_window->display();
}