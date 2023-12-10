#pragma once

#include "Shape.h"

class BezierSpline : public Shape{
public:
	BezierSpline() {
		m_type = SHAPE::BEZIER_SPLINE;
		m_lastPointInfo = { 0, 0 };
	}
	virtual ~BezierSpline() { };
	BezierSpline(sf::Vector2f s)
	{
		m_type = SHAPE::BEZIER_SPLINE;
		m_controlPoints = sf::VertexArray(sf::Lines, 1);
		m_controlPoints[0].position = s;
		m_controlPoints[0].color = sf::Color(255, 255, 255, 50);
		m_curve = sf::VertexArray(sf::LineStrip, 1);
		m_curve[0].position = s;
		m_curveToDraw = sf::VertexArray(sf::LinesStrip, 1);
		m_curveToDraw[0].position = s;
		m_curveToDraw[0].color = sf::Color(255, 255, 255, 50);
	}

	void AddPoint(sf::Vector2f v)
	{
		sf::Vector2f cp1, cp2, knot = v, directionVector, lastPoint = m_controlPoints[m_controlPoints.getVertexCount() - 1].position, startToFinish = v - lastPoint;
		if (m_controlPoints.getVertexCount() > 1)
		{
			directionVector = lastPoint - m_controlPoints[m_controlPoints.getVertexCount() - 2].position;
		}
		else
		{
			directionVector = v - lastPoint;
		}
		
		cp1 = lastPoint + directionVector;
		cp2 = lastPoint + directionVector * 0.75f + startToFinish * 0.5f + normalize(sf::Vector2f(-directionVector.y, directionVector.x)) * 20.0f;
		
		m_controlPoints.append(cp1);
		m_controlPoints.append(cp2);
		m_controlPoints.append(knot);

		m_controlPoints[m_controlPoints.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
		Recalculate();
		AdditionalCalculations();
	}

	void SetPoint(size_t i, sf::Vector2f v, int flag = 0)
	{
		if (i == 0 || i % 3 == 0)
		{
			sf::Vector2f displacement = v - m_controlPoints[i].position;
			m_controlPoints[i].position = v;
			if (i > 1)
			{
				m_controlPoints[i - 1].position += displacement;
			}
			if (i < m_controlPoints.getVertexCount() - 2 && i != 0)
			{
				m_controlPoints[i + 1].position += displacement;
			}
		}
		else
		{
			m_controlPoints[i].position = v;
		}
		Recalculate();
		AdditionalCalculations();
	}

	void Draw() override;
	void DrawControlPoints();

	std::pair<size_t, int> IsSelected() const override;
private:
	void Recalculate() override;
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);
	void CalcSection(size_t i);

	const float m_pointCollisionBox = 10.0f;
	const float m_controlPointRadius = 5.0f;

};