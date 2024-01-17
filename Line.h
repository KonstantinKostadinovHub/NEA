#pragma once

#include "SFML/Graphics.hpp"

#include "Shape.h"

#include <iostream>

class Line : public Shape {
public:
	Line() { m_type = SHAPE::LINE; };
	virtual ~Line() {};
	Line(sf::Vector2f s) { m_type = SHAPE::LINE; m_controlPoints = sf::VertexArray(sf::LinesStrip, 1); m_controlPoints[0].position = s; m_curve = sf::VertexArray(sf::LinesStrip, 1); m_curve[0].position = s; };

	void Recalculate();

	void Draw() override;
private:

};