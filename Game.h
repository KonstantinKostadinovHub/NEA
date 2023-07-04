#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

#include "defines.h"

#include "Config.h"
#include "Hand.h"

class Game {
public:
	Game();
	~Game();

	void init(GAME_MODE _mode);

	void run();

	static void addObj(sf::Vector2i v, CARD c, int team);

private:
	void initTowers();

	void update();
	void draw();

	static Config* config;
	GAME_MODE mode;
	Hand hand;

	std::unique_ptr<sf::RectangleShape> background;
	sf::RectangleShape arena;

	static std::vector<std::unique_ptr<Object>> objects;
};