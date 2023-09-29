#include "BezierCurve.h"

#include "defines.h"

#include "World.h"

void BezierCurve::SetPoint(std::size_t i, sf::Vector2f v, int flag)
{
	m_controlPoints[i].position = v;
	Recalculate();
}

void BezierCurve::AddPoint(sf::Vector2f v)
{
	m_controlPoints.append(v);
	m_controlPoints[m_controlPoints.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
	Recalculate();
}

void BezierCurve::Draw()
{
	World::draw(m_curve);
	World::draw(m_controlPoints);
	for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
	{
		auto circle = sf::CircleShape(m_radius, 10);
		circle.setPosition(m_controlPoints[i].position - sf::Vector2f(m_radius, m_radius));
		World::draw(circle);
	}
}

std::pair<size_t, int> BezierCurve::IsSelected() const
{
	for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
	{
		if (inCircle(m_controlPoints[i].position, m_radius, sf::Vector2f(Input::MouseCoor())))
		{
			return { i, 0 };
		}
	}
	return { size_t(-1), -1 };
}

void BezierCurve::Recalculate()
{
	m_curve.clear();
	m_curve.append(m_controlPoints[0].position);
	const size_t controlPointsCount = m_controlPoints.getVertexCount();
	for (auto i = 0; i < m_samples * controlPointsCount - 2; i++)
	{
		m_curve.append(LerpRecursively(m_controlPoints, (1.0f * i) / (m_samples * controlPointsCount - 2)));
	}
	m_curve.append(m_controlPoints[m_controlPoints.getVertexCount() - 1]);
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
