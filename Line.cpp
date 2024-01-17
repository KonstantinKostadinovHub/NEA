#include "Line.h"

#include "World.h"

void Line::Recalculate()
{
	m_curve.clear();
	for (size_t i = 0; i < m_controlPoints.getVertexCount() - 1; i++)
	{
		for (size_t t = 1; t <= m_samples; t++)
		{
			m_curve.append(lerp(m_controlPoints[i].position, m_controlPoints[i + 1].position, 1.0f / float(m_samples) * t));
		}
	}
}

void Line::Draw()
{
	World::draw(m_curve);
	for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
	{
		auto circle = sf::CircleShape(m_controlPointRadius, 10);
		circle.setPosition(m_controlPoints[i].position - sf::Vector2f(m_controlPointRadius, m_controlPointRadius));
		World::draw(circle);
	}
}
