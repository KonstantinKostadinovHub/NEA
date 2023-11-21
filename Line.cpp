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

void Line::Recalculate()
{
	m_curve.clear();
	for (size_t i = 0; i < m_line.getVertexCount() - 1; i++)
	{
		for (size_t t = 1; t <= m_pointsPerSection; t++)
		{
			m_curve.append(lerp(m_line[i].position, m_line[i + 1].position, 1.0f / float(m_pointsPerSection) * t));
		}
	}
}

void Line::Draw()
{
	World::draw(m_curve);
}

std::pair<size_t, int> Line::IsSelected() const
{
	return { size_t(-1), 0 };
}
