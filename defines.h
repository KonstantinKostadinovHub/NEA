#pragma once

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

enum class STATE {
	MENU = 1,
	PLAYER = 2,
	AI = 3,
	TRAINING = 4,
};

enum class GAME_MODE {
	PLAYER = 1,
	AI = 2,
	TRAINING = 3,
};

enum class CARD {
	NONE = 0,
	KNIGHT = 1,
	FIREBALL = 2,
	SKELETONS = 3,
	GIANT = 4,
	PIGEONS = 5,
	WIZARD = 6,
	DRAGON = 7,
	BALLOON = 8,
	SIZE = 9,
};

const int GAME_WINDOW_X = 696;
const int GAME_WINDOW_Y = 105;
const int GAME_WINDOW_W = 530;
const int GAME_WINDOW_H = 720;

const int MAIN_WINDOW_X = 656;
const int MAIN_WINDOW_Y = 0;
const int MAIN_WINDOW_W = 608;
const int MAIN_WINDOW_H = 1080;

const std::string CONFIG_FOLDER = "config/";
const std::string CARDS_FOLDER = "cards/";
const std::string UI_FOLDER = "ui/";
const std::string IMAGE_FOLDER = "img/";

static int distance(int x1, int y1, int x2, int y2) {
	return std::sqrt(std::pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

static sf::Vector2f makeUnit(sf::Vector2f v) {
	float l = std::sqrt(v.x * v.x + v.y * v.y);
	return sf::Vector2f(v.x / l, v.y / l);
}

static bool inRect(sf::Vector2i p, sf::RectangleShape r) {
	if (p.x > r.getPosition().x && p.x < r.getPosition().x + r.getSize().x
		&& p.y > r.getPosition().y && p.y < r.getPosition().y + r.getSize().y) {
		return true;
	}
	return false;
}

static std::string cardName(CARD c) {
	switch (c)
	{
	case CARD::NONE:
		break;
	case CARD::KNIGHT:
		return "knight";
		break;
	case CARD::FIREBALL:
		return "fireball";
		break;
	case CARD::SKELETONS:
		return "skeletons";
		break;
	case CARD::GIANT:
		return "giant";
		break;
	case CARD::PIGEONS:
		return "pigeons";
		break;
	case CARD::WIZARD:
		return "wizard";
		break;
	case CARD::DRAGON:
		return "dragon";
		break;
	case CARD::BALLOON:
		return "balloon";
		break;
	default:
		break;
	}
}