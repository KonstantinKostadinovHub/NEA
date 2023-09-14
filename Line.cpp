#include "Line.h"

#include "World.h"

void Line::setColor(sf::Color c)
{
	m_color = c;
	m_line[0].color = c;
	m_line[1].color = c;
}

void Line::setVertex(std::size_t i, sf::Vector2f v)
{
	m_line[i].position = v;
}

void Line::draw()
{
	World::draw(m_line);
}
