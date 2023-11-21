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
		sf::Vector2f cp1, cp2, knot = v, directionVector, lastPoint = m_controlPoints[m_controlPoints.getVertexCount() - 1].position;
		directionVector = v - lastPoint;
		
		cp1 = lastPoint + directionVector * 0.25f + sf::Vector2f(- directionVector.y, directionVector.x) * 0.2f;
		cp2 = lastPoint + directionVector * 0.75f + sf::Vector2f(- directionVector.y, directionVector.x) * 0.2f;
		
		m_controlPoints.append(cp1);
		m_controlPoints.append(cp2);
		m_controlPoints.append(knot);

		m_controlPoints[m_controlPoints.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
		Recalculate();
		AdditionalCalculations();
	};;

	void Draw() override;

	std::pair<size_t, int> IsSelected() const override;
private:
	void Recalculate() override;
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);
	void CalcSection(size_t i);

	const float m_pointCollisionBox = 10.0f;
	const float m_controlPointRadius = 5.0f;

};