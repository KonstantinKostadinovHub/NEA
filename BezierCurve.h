#pragma once

#include "SFML/Graphics.hpp"

#include "Shape.h"

class BezierCurve : public Shape{
public:
	BezierCurve() {};
	virtual ~BezierCurve() {};
	BezierCurve(sf::Vector2f s) {
		m_controlPointLines = sf::VertexArray(sf::LineStrip, 1);
		m_controlPointLines[0].position = s;
		m_controlPointLines[0].color = sf::Color(255, 255, 255, 100);
		m_curve = sf::VertexArray(sf::LineStrip, 1);
		m_curve[0].position = s;
	};

	void setVertex(std::size_t i, sf::Vector2f v);

	void AddPoint(sf::Vector2f v) override;

	void Draw() override;
private:
	void Recalculate();
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);
	
	sf::VertexArray m_curve;
	sf::VertexArray m_controlPointLines;

	float m_samples = 100;

	sf::Color m_color;
};