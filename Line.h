#pragma once

#include "SFML/Graphics.hpp"

#include "Shape.h"

#include <iostream>

class Line : public Shape {
public:
	Line() { m_type = SHAPE::LINE; };
	virtual ~Line() {};
	Line(sf::Vector2f s) { m_type = SHAPE::LINE; m_line = sf::VertexArray(sf::Lines, 2); m_line[0].position = s; m_line[1].position = s; };

	void setColor(sf::Color c);
	void setVertex(std::size_t i, sf::Vector2f v);

	void SetPoint(size_t index, sf::Vector2f v, int flag = 0) override;
	void AddPoint(sf::Vector2f e) override
	{
		m_line[1].position = e;
		std::cout << m_line[1].position.x << " " << m_line[1].position.y << "\n";
	};

	void Draw() override;

	size_t GetControlPointsCount() override { return m_line.getVertexCount(); };

	std::pair<size_t, int> IsSelected() const override;
private:
	sf::VertexArray m_line;

	sf::Color m_color;
};