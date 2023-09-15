#pragma once

#include "SFML/Graphics.hpp"

#include "Shape.h"

#include <iostream>

class Line : public Shape {
public:
	Line(){};
	virtual ~Line() {};
	Line(sf::Vector2f s) { m_line = sf::VertexArray(sf::Lines, 2); m_line[0].position = s; m_line[1].position = s; };

	void setColor(sf::Color c);
	void setVertex(std::size_t i, sf::Vector2f v);

	void AddPoint(sf::Vector2f e) override
	{
		m_line[1].position = e;
		std::cout << m_line[1].position.x << " " << m_line[1].position.y << "\n";
	};

	void Draw() override;
private:
	sf::VertexArray m_line;

	sf::Color m_color;
};