#pragma once

#include "SFML/Graphics.hpp"

#include "Component.h"

#include "defines.h"

class Transform : public Component {
public:
	Transform(){};
	virtual ~Transform(){};

	void init(sf::FloatRect _rect, bool _onGround, bool _isBuilding, std::string image) {
		rect = _rect; onGround = _onGround;
		
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromFile(image)) {
			printf("Error: Image not found ");
		}

		sprite.setTexture(texture);
		sprite.setSize({ rect.width, rect.height });

		isBuilding = _isBuilding;
		textureLocation = image;
	};

	void action() override { sprite.setPosition(GAME_WINDOW_X + rect.left, GAME_WINDOW_Y + rect.top); };
	Transform* clone() const override {
		return new Transform(*this);
	}

	sf::Vector2f getPosition() { return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2); }
	void move(sf::Vector2f v) { rect.left += v.x, rect.top += v.y; };

	std::string textureLocation;

	bool onGround;
	bool isBuilding;

	sf::FloatRect rect;
	sf::RectangleShape sprite;
};