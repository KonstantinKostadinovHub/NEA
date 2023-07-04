#pragma once

#include <SFML/Graphics.hpp>

/* the UI showing :
	- all of our available cards
	- the upcoming card
	- our elixir bar
	- the (elixir) cost for each card
 */

#include "Config.h"

class Hand {
public:
	Hand() {};
	virtual ~Hand(){};
	
	/*
	* @param cards - the cards that we have in the beggining
	* @param textures - the texture for each of these cards
	*/
	
	void init(const std::vector<CARD> _cards) {
		background.setPosition({ MAIN_WINDOW_X + 108, MAIN_WINDOW_Y + 876 });
		background.setSize({ 500, 205 });

		for (int i = 0; i < 4; i++) {
			cardUI[i].first.setPosition({ float(MAIN_WINDOW_X + 140 + 115 * i), MAIN_WINDOW_Y + 900});
			cardUI[i].first.setSize({ 100, 120 });
		}

		Config* config = Config::getInstance();

		for (auto card : _cards) {
			cards.push_back(card);
			textures.insert({ card, &config->cardsUI.at(card)});
		}

		for (int i = 0; i < 4; i++) {
			cardUI[i].first.setTexture(textures.at(cards[i]));
			cardUI[i].second = cards[i];
		}
	}

	std::vector<CARD> cards;
	std::unordered_map<CARD, sf::Texture*> textures;

	sf::RectangleShape background;
	std::pair<sf::RectangleShape, CARD> cardUI[4];

	void update();
	void draw();

private:
	bool dragging;

	CARD selectedCard;
};
