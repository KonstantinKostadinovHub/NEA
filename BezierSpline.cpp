#include "BezierSpline.h"

#include "Input.h"
#include "World.h"

void BezierSpline::Draw()
{
	UpdateLastVisiblePoint();
	World::draw(m_curveToDraw);
	DrawControlPoints();
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

void BezierSpline::DrawControlPoints()
{
	sf::VertexArray v(sf::LineStrip);

	if (m_controlPoints.getVertexCount() > 1)
	{
		v.append(m_controlPoints[0]);
		v.append(m_controlPoints[1]);
		v[0].color = sf::Color(255, 255, 255, 30);
		v[1].color = sf::Color(255, 255, 255, 30);

		World::draw(v);
		for (size_t i = 2; i < m_controlPoints.getVertexCount() - 2; i+=3)
		{
			v[0].position = m_controlPoints[i].position;
			v[1].position = m_controlPoints[i + 1].position;
			World::draw(v);

			v[0].position = m_controlPoints[i + 2].position;
			v[1].position = m_controlPoints[i + 1].position;
			World::draw(v);
		}

		v[0].position = m_controlPoints[m_controlPoints.getVertexCount() - 2].position;
		v[1].position = m_controlPoints[m_controlPoints.getVertexCount() - 1].position;
		World::draw(v);
	}
}

void BezierSpline::Recalculate()
{
	const size_t controlPointsCount = m_controlPoints.getVertexCount();
	m_lastPointInfo.first = 0;
	m_curveToDraw.clear();
	m_curve.clear();
	m_curve.append(m_controlPoints[0].position);
	if (controlPointsCount > 1)
	{
		CalcSection(0);

		for (auto i = 3; i < controlPointsCount - 3; i += 3)
		{
			CalcSection(i);
		}
		m_curve.append(m_controlPoints[controlPointsCount - 1].position);
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
}
