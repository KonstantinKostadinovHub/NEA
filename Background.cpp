#include "Background.h"
#include "World.h"

void Background::Init()
{
	m_tex.loadFromFile(IMAGE_FOLDER + "bg_dot.png");
	m_sprite.setTexture(m_tex);
	m_sprite.setScale(sf::Vector2f(0.5f, 0.5f ));
}

void Background::Draw()
{
	sf::Vector2f itr = {0, 0};

	while (Step(itr)) {};
}

bool Background::Step(sf::Vector2f& itr)
{
	itr.x += m_distanceForPoint;
	if (itr.x > m_boundary.x)
	{
		itr.x = 0.0f;
		itr.y += m_distanceForPoint;
		if (itr.y > m_boundary.y)
		{
			return false;
		}
	}
	m_sprite.setPosition(itr);
	World::draw(m_sprite);

	return true;
}