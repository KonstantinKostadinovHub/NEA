#include "BezierSpline.h"

#include "Input.h"
#include "World.h"

void BezierSpline::Draw()
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

std::pair<size_t, int> BezierSpline::IsSelected() const
{
	for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
	{
		if (inCircle(m_controlPoints[i].position, m_pointCollisionBox, sf::Vector2f(Input::MouseCoor())))
		{
			return { i, 0 };
		}
	}
	return { size_t(-1), -1 };
}

void BezierSpline::Recalculate()
{
	m_lastPointInfo.first = 0;
	m_curve.clear();
	m_curve.append(m_controlPoints[0].position);
	if (m_controlPoints.getVertexCount() > 1)
	{
		const size_t controlPointsCount = m_controlPoints.getVertexCount();
		CalcSection(0);

		for (auto i = 3; i < controlPointsCount - 3; i += 3)
		{
			CalcSection(i);
		}
	}
}

sf::Vector2f BezierSpline::LerpRecursively(sf::VertexArray vertices, float t)
{
	sf::Vector2f res = vertices[0].position;
	if (vertices.getVertexCount() > 1)
	{
		sf::VertexArray _v = sf::VertexArray(sf::Points, 0);
		for (size_t i = 1; i < vertices.getVertexCount(); i++)
		{
			_v.append(lerp(vertices[i - 1].position, vertices[i].position, t));
		}
		res = LerpRecursively(_v, t);
	}

	return res;
}

void BezierSpline::CalcSection(size_t i)
{
	sf::VertexArray section;
	for (size_t j = 0; j < 4; j++)
	{
		section.append(m_controlPoints[i + j].position);
	}

	for (size_t j = 0; j < m_samples; j++)
	{
		m_curve.append(LerpRecursively(section, 1.0f * j / m_samples));
	}
	m_curve.append(section[3].position);
}
