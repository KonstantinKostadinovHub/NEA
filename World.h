#pragma once

#include <memory>
#include <iostream>

#include "Game.h"
#include "Menu.h"

class World {
public:
	World();
	virtual ~World();

	void init();
	void run();

	bool isOpen() { return m_window->isOpen(); };

	static void draw(const sf::VertexArray& drawable) { m_window.get()->draw(drawable); };
	static void draw(const sf::Drawable& drawable) { m_window.get()->draw(drawable); };
	static void draw(const sf::Sprite drawable) { m_window.get()->draw(drawable); };
	static void draw(const sf::RectangleShape& drawable) { m_window->draw(drawable);  };

	static sf::RenderWindow* getWindow() { return m_window.get(); };

	static void setState(SCENE _state) { m_state = _state; }
private:
	static std::shared_ptr<sf::RenderWindow> m_window;
	sf::Clock deltaClock;

	float lastTick;

	static SCENE m_state;

	Game m_game;
	Menu m_menu;
	Input& m_input = Input::GetInstance();

	//Input
	static bool isLeftClicked;
	static bool isLeftPressed;

	void ShowFPS(float passed);
};