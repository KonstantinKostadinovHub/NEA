#pragma once

#include "SFML/Graphics.hpp"

class Background {
public:
	Background() { };
	virtual ~Background() { };

	void Init();
	void Draw();
private:
	const float m_distanceForPoint = 30.0f;
	const sf::Vector2f m_boundary = { 1920.0f, 1080.0f };

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	bool Step(sf::Vector2f& itr);
};