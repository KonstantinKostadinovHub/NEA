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
	UpdateLastVisiblePoint();
	World::draw(m_curveToDraw);
	World::draw(m_controlPoints);
	for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
	{
		auto circle = sf::CircleShape(m_radius, 10);
		circle.setPosition(m_controlPoints[i].position - sf::Vector2f(m_radius, m_radius));
		World::draw(circle);
	}
	//World::draw(m_osculatingCircleRadiuses);
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
	m_lastPointInfo.first = 0;
	m_curve.clear();
	m_curve.append(m_controlPoints[0].position);
	const size_t controlPointsCount = m_controlPoints.getVertexCount();
	for (auto i = 0; i < m_samples * controlPointsCount - 2; i++)
	{
		m_curve.append(LerpRecursively(m_controlPoints, (1.0f * i) / (m_samples * controlPointsCount - 2)));
	}
	m_curve.append(m_controlPoints[m_controlPoints.getVertexCount() - 1]);

	CDerivative(m_curve, m_firstDerivative);
	CDerivative(m_firstDerivative, m_secondDerivative);
	COsculatingRadiuses();
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

void BezierCurve::UpdateLastVisiblePoint()
{	
	if (m_lastPointInfo.first + 1 != m_curve.getVertexCount())
	{
		if (m_msPerPoint < World::GetTimeInMs() - m_lastPointInfo.second)
		{
			m_lastPointInfo.second = World::GetTimeInMs();
			m_lastPointInfo.first++;
			m_curveToDraw.clear();
			for (size_t i = 0; i <= m_lastPointInfo.first; i++)
			{
				m_curveToDraw.append(m_curve[i].position);
			}
		}
	}
}
