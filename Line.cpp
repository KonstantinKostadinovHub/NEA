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

void Line::SetPoint(size_t index, sf::Vector2f v, int flag)
{

}


void Line::Draw()
{
	World::draw(m_line);
}

std::pair<size_t, int> Line::IsSelected() const
{
	return { size_t(-1), 0 };
}
