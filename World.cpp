#include "World.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <string>

std::unique_ptr<sf::RenderWindow> World::window = nullptr;
STATE World::state = STATE::MENU;
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
	window.reset(new sf::RenderWindow(sf::VideoMode(1920, 1080), "Window Title", sf::Style::Fullscreen, sf::ContextSettings()));
	ImGui::SFML::Init(*window);
	
	// Must be initialised after we have created the window
	game.init(GAME_MODE::PLAYER);
	menu.init();
}

void World::run()
{
	isLeftClicked = false;

	while (window->pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				isLeftClicked = true;
				isLeftPressed = true;
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				isLeftPressed = false;
			}
		}
	}

	window->clear(sf::Color(18, 33, 43));

	ImGui::SFML::Update(*window, deltaClock.restart());

	if (state == STATE::MENU) {
		menu.run();
	}else if (state == STATE::PLAYER) {
		game.run();
	}else if (state == STATE::AI) {
		menu.run();
	}else if (state == STATE::TRAINING) {
		menu.run();
	}

	ImGui::SFML::Render(*window);
	window->display();
}

sf::Vector2i World::getMouse()
{
	return sf::Mouse::getPosition(*window);
}

bool World::isClicked()
{
	return isLeftClicked;
}

bool World::isPressed()
{
	return isLeftPressed;
}
