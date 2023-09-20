#include "BezierCurve.h"

#include "defines.h"

#include "World.h"

void BezierCurve::setVertex(std::size_t i, sf::Vector2f v)
{
	m_controlPointLines[i].position = v;
	Recalculate();
}

void BezierCurve::AddPoint(sf::Vector2f v)
{
	m_controlPointLines.append(v);
	m_controlPointLines[m_controlPointLines.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
	Recalculate();
}

void BezierCurve::Draw()
{
	World::draw(m_controlPointLines);
	
	World::draw(m_curve);
}

void BezierCurve::Recalculate()
{
	m_curve.clear();
	m_curve.append(m_controlPointLines[0]);
	for (auto i = 0; i < m_samples; i++)
	{
		std::cout << LerpRecursively(m_controlPointLines, 1.0f / m_samples * i).x << " " << LerpRecursively(m_controlPointLines, 1.0f / m_samples * i).y << " \n";
		m_curve.append(LerpRecursively(m_controlPointLines, 1.0f / m_samples * i));
	}
	m_curve.append(m_controlPointLines[m_controlPointLines.getVertexCount() - 1]);
	std::cout << " \n";
}

sf::Vector2f BezierCurve::LerpRecursively(const sf::VertexArray vertices, float t)
{
	sf::Vector2f res = vertices[0].position;
	if (vertices.getVertexCount() > 1) 
	{
		sf::VertexArray _v = sf::VertexArray(sf::Points, 0);
		for(size_t i = 1; i < vertices.getVertexCount(); i ++)
		{
			_v.append(lerp(vertices[i - 1].position, vertices[i].position, t));
		}
		res = LerpRecursively(_v, t);
	}

	return res;
}
