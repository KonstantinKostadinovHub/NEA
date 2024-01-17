#pragma once

#include "SFML/Graphics.hpp"

#include "ControlPointArray.h"
#include "Shape.h"

class BezierCurve : public Shape{
public:
	BezierCurve() {
		m_type = SHAPE::BEZIER_CURVE; m_lastPointInfo = { 0, 0 };
	}
	virtual ~BezierCurve() {};
	BezierCurve(sf::Vector2f s) {
		m_type = SHAPE::BEZIER_CURVE;
		m_controlPoints = sf::VertexArray(sf::LineStrip, 1);
		m_controlPoints[0].position = s;
		m_controlPoints[0].color = sf::Color(255, 255, 255, 50);
		m_curve = sf::VertexArray(sf::LineStrip, 1);
		m_curve[0].position = s;
		m_curveToDraw = sf::VertexArray(sf::LinesStrip, 1);
		m_curveToDraw[0].position = s;
		m_curveToDraw[0].color = sf::Color(255, 255, 255, 50);
	};

	void Draw() override;

	std::pair<size_t, int> IsSelected() const override;
private:
	void Recalculate();
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);

	sf::Color m_color;
};