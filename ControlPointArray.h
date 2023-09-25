#pragma once

#include "SFML/Graphics.hpp"

class ControlPointArray
{
public:
	ControlPointArray();
	virtual ~ControlPointArray();

	void AddPoint(sf::Vector2f p);
	void RemovePoint(size_t index);

	sf::VertexArray GetVertexArray();
	
	size_t IsSelected() const;

	void Draw();
	
	static float m_radius;
	sf::VertexArray m_points;
};