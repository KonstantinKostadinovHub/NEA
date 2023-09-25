#include "ControlPointArray.h"

#include "defines.h"

#include "World.h"

float ControlPointArray::m_radius = 10.0f;

ControlPointArray::ControlPointArray()
{
	m_points.setPrimitiveType(sf::LineStrip);
}

ControlPointArray::~ControlPointArray()
{
}

void ControlPointArray::AddPoint(sf::Vector2f p)
{
	m_points.append(p);
	m_points[m_points.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
}

void ControlPointArray::RemovePoint(size_t index)
{
	sf::VertexArray data;
	for (size_t i = 0; i < m_points.getVertexCount(); i++)
	{
		if(i != index)
		{
			data.append(m_points[i]);
		}
	}
	m_points.clear();
	m_points = data;
}

sf::VertexArray ControlPointArray::GetVertexArray()
{
	return m_points;
}

size_t ControlPointArray::IsSelected() const
{
	for(size_t i = 0; i < m_points.getVertexCount(); i++)
	{
		if (inCircle(m_points[i].position, m_radius, sf::Vector2f(Input::MouseCoor())))
		{
			return i;
		}
	}
	return size_t(-1);
}

void ControlPointArray::Draw()
{
	World::draw(m_points);

	sf::CircleShape circle = sf::CircleShape(m_radius, 10);
	for (size_t i = 0; i < m_points.getVertexCount(); i++)
	{
		circle.setPosition(m_points[i].position - sf::Vector2f(m_radius, m_radius));
		World::draw(circle);
	}
}
