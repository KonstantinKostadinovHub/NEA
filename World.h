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

	bool isOpen() { return window->isOpen(); };

	static void draw(const sf::VertexArray drawable) { window.get()->draw(drawable); };
	static void draw(const sf::Drawable& drawable) { window.get()->draw(drawable); };
	static void draw(const sf::Sprite drawable) { window.get()->draw(drawable); };
	static void draw(const sf::RectangleShape& drawable) { window->draw(drawable);  };

	static sf::RenderWindow* getWindow() { return window.get(); };

	static void setState(SCENE _state) { state = _state; }

	// Input
	static sf::Vector2i getMouse();
	static bool isClicked();
	static bool isPressed();

private:
	static std::unique_ptr<sf::RenderWindow> window;
	sf::Clock deltaClock;
	sf::Event event;

	float lastTick;

	static SCENE state;

	Game game;
	Menu menu;

	//Input
	static bool isLeftClicked;
	static bool isLeftPressed;
};