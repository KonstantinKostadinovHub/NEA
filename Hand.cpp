#include "Hand.h"

#include "World.h"

void Hand::update()
{
	if (World::isPressed()) {
		if (!dragging) {
			for (const auto& card : cardUI) {
				if (inRect(World::getMouse(), card.first)) {
					selectedCard = card.second;
				}
			}
		}
		dragging = true;
	}
	else {
		if (dragging) {
			Game::addObj(World::getMouse(), selectedCard, 1);
		}
		dragging = false;
	}

	if (!dragging) {
		selectedCard = CARD::NONE;
	}
}

void Hand::draw()
{
	World::draw(background);

	for (const auto& card : cardUI) {
		if(selectedCard != card.second){
			World::draw(card.first);
		}
		else {
			// TODO: change later with actual models
			const float cardScale = 0.4f;
			sf::RectangleShape rect = card.first;

			rect.setScale(cardScale, cardScale);
			rect.setPosition(sf::Vector2f(World::getMouse().x - rect.getSize().x * cardScale / 2, World::getMouse().y - rect.getSize().y * cardScale / 2));
			World::draw(rect);
		}
	}
}
