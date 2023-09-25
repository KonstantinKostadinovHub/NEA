#pragma once

#include "SFML/Graphics.hpp"

#include "ControlPointArray.h"
#include "Shape.h"

class BezierCurve : public Shape{
public:
	BezierCurve() {};
	virtual ~BezierCurve() {};
	BezierCurve(sf::Vector2f s) {
		m_controlPoints = sf::VertexArray(sf::LinesStrip, 1);
		m_controlPoints[0].position = s;
		m_controlPoints[0].color = sf::Color(255, 255, 255, 50);
		m_curve = sf::VertexArray(sf::LineStrip, 1);
		m_curve[0].position = s;
	};


	void AddPoint(sf::Vector2f v) override;
	void SetPoint(std::size_t i, sf::Vector2f v, int flag = 0) override;

	void Draw() override;

	std::pair<size_t, int> IsSelected() const override;
private:
	void Recalculate();
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);
	
	sf::VertexArray m_curve;
	sf::VertexArray m_controlPoints;

	float m_samples = 100;
	float m_radius = 10;

	sf::Color m_color;
};