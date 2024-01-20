#include "BezierCurve.h"

#include "defines.h"

#include "World.h"

void BezierCurve::Draw()
{
	UpdateLastVisiblePoint();
	World::draw(m_curveToDraw);
	World::draw(m_controlPoints);
	for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
	{
		auto circle = sf::CircleShape(m_controlPointRadius, 10);
		circle.setPosition(m_controlPoints[i].position - sf::Vector2f(m_controlPointRadius, m_controlPointRadius));
		World::draw(circle);
	}
	if (m_drawOsculatingCircleGraph) 
	{ 
		if (m_osculatingCircleRadiuses.getVertexCount() == 0) COsculatingRadiuses();
		World::draw(m_osculatingCircleRadiuses);
	}
}

void BezierCurve::Recalculate()
{
	const size_t controlPointsCount = m_controlPoints.getVertexCount();
	if (controlPointsCount != 0)
	{
		m_lastPointInfo.first = 0;
		m_curve.clear();
		for (auto i = 0; i < m_samples * controlPointsCount; i++)
		{
			m_curve.append(LerpRecursively(m_controlPoints, (1.0f * i) / (m_samples * controlPointsCount)));
		}
		m_curve.append(m_controlPoints[m_controlPoints.getVertexCount() - 1]);
	}
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
