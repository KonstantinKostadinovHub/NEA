#pragma once

#include "SFML/Graphics.hpp"

#include <map>

enum class INFO_CARD {
	NONE = 0,
	LINE = 1,
	BEZIER_CURVES = 2,
	BEZIER_SPLINES = 3,
	HERMITE = 4,
	FIRST_DERIVATIVE = 5,
	COUNT = 6
	// LIST ALL
};

class InfoCard {
public:
	InfoCard(){};
	virtual ~InfoCard(){};

	void Init();

	void Draw();

	static void SetInfoCard(INFO_CARD card);

private:
	static INFO_CARD m_current;

	static std::map<INFO_CARD, sf::Texture> m_cards;

	static sf::Sprite m_infoCardSp;

	void AddCard(INFO_CARD c);
};