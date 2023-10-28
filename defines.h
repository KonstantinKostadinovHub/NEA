#pragma once

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"

enum class SCENE{
	MENU = 1,
	PLAYGROUND = 2
};

enum class SHAPE {
	NONE = 0,
	LINE = 1,
	BEZIER_CURVE = 2,
};

const std::string CONFIG_FOLDER = "config/";
const std::string UI_FOLDER = "ui/";
const std::string IMAGE_FOLDER = "img/";

constexpr ImGuiWindowFlags DEFAULT_WINDOW = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;

static int distance(int x1, int y1, int x2, int y2) {
	return std::sqrt(std::pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

static float magnitude(sf::Vector2f a)
{
	return sqrt(a.x * a.x + a.y * a.y);
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

static unsigned long long binomialCoefficient(unsigned long long n, unsigned long long k) {
	if (k > n - k) {
		k = n - k; // Optimization to reduce calculations
	}

	unsigned long long result = 1;

	for (unsigned long long i = 0; i < k; ++i) {
		result *= (n - i);
		result /= (i + 1);
	}

	return result;
}

/*
* @param c - centre of circle
* @param r - radius
* @param t - target (point to check)
*/
static bool inCircle(const sf::Vector2f& c, const float& r, const sf::Vector2f& t) 
{
	if ((t.x - c.x) * (t.x - c.x) + (t.y - c.y) * (t.y - c.y) <= r * r) return true;
	return false;
}

static sf::Vector2f lerp(const sf::Vector2f& point1, const sf::Vector2f& point2, float t) {
	t = std::max(0.0f, std::min(1.0f, t));

	sf::Vector2f result;
	result.x = point1.x + (point2.x - point1.x) * t;
	result.y = point1.y + (point2.y - point1.y) * t;

	return result;
}