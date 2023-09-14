#pragma once

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

enum class SCENE{
	MENU = 1,
	PLAYGROUND = 2
};

const std::string CONFIG_FOLDER = "config/";
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

/*
* @param c - centre of circle
* @param r - radius
* @param t - target (point to check)
*/
static bool inCircle(sf::Vector2f c, float r, sf::Vector2f t) {
	if ((t.x - c.x) * (t.x - c.x) + (t.y - c.y) * (t.y - c.y) <= r * r) return true;
	return false;
}