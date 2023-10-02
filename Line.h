#pragma once

#include "SFML/Graphics.hpp"

#include "Shape.h"

#include <iostream>

class Line : public Shape {
public:
	Line() { m_type = SHAPE::LINE; };
	virtual ~Line() {};
	Line(sf::Vector2f s) { m_type = SHAPE::LINE; m_line = sf::VertexArray(sf::LinesStrip, 1); m_line[0].position = s; m_curve = sf::VertexArray(sf::LinesStrip, 1); m_curve[0].position = s; };

	void setColor(sf::Color c);
	void setVertex(std::size_t i, sf::Vector2f v);

	void SetPoint(size_t index, sf::Vector2f v, int flag = 0) override;
	void AddPoint(sf::Vector2f e) override
	{
		m_line.append(e);
		Recalculate();
	};
	void Recalculate();

	void Draw() override;

	size_t GetControlPointsCount() override { return m_line.getVertexCount(); };
	size_t GetPointsPerSection() const override { return m_pointsPerSection; };

	std::pair<size_t, int> IsSelected() const override;
private:
	sf::VertexArray m_line;

	sf::Color m_color;
	const size_t m_pointsPerSection = 20;
};