#include "InfoCard.h"

#include "World.h"

INFO_CARD InfoCard::m_current = INFO_CARD::NONE;
sf::Sprite InfoCard::m_infoCardSp = sf::Sprite();
std::map<INFO_CARD, sf::Texture> InfoCard::m_cards = std::map<INFO_CARD, sf::Texture>();

void InfoCard::Init()
{
	for (size_t i = 0; i < size_t(INFO_CARD::COUNT); i++)
	{
		AddCard(INFO_CARD(i));
	}
	m_infoCardSp.setPosition(1413, 542);
}

void InfoCard::Draw()
{
	World::draw(m_infoCardSp);
}

void InfoCard::SetInfoCard(INFO_CARD card)
{
	m_infoCardSp.setTexture(m_cards[card]);
	m_current = card;
}


void InfoCard::AddCard(INFO_CARD i)
{
	m_cards.insert({ i, sf::Texture() });
	m_cards[i].loadFromFile(IMAGE_FOLDER + UI_FOLDER + "info_cards/card_" + std::to_string(size_t(i)) + ".png");
}