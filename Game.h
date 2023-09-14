#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

#include "defines.h"

#include "Config.h"

class Game {
public:
	Game();
	~Game();

	void init();

	void run();

private:
	void update();
	void draw();

	static std::shared_ptr<Config> config;

	sf::RectangleShape background;
};