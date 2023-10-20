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
		m_controlPoints = sf::VertexArray(sf::LinesStrip, 1);
		m_controlPoints[0].position = s;
		m_controlPoints[0].color = sf::Color(255, 255, 255, 50);
		m_curve = sf::VertexArray(sf::LineStrip, 1);
		m_curve[0].position = s;
		m_curveToDraw = sf::VertexArray(sf::LinesStrip, 1);
		m_curveToDraw[0].position = s;
		m_curveToDraw[0].color = sf::Color(255, 255, 255, 50);
	};


	void AddPoint(sf::Vector2f v) override;
	void SetPoint(std::size_t i, sf::Vector2f v, int flag = 0) override;

	size_t GetControlPointsCount() override { return m_controlPoints.getVertexCount(); };
	size_t GetPointsPerSection() const override { return m_samples; };

	void Draw() override;

	std::pair<size_t, int> IsSelected() const override;
private:
	void Recalculate();
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);
	
	// used for draw animation
	void UpdateLastVisiblePoint();

	sf::VertexArray m_curveToDraw;
	sf::VertexArray m_controlPoints;
	
	const size_t m_samples = 20;
	const float m_radius = 10;

	sf::Color m_color;

	/*
	* size_t first - index of the point
	* int second - timestamp in ms when it was last drawn
	*/
	std::pair<size_t, int> m_lastPointInfo;

	const size_t m_msPerPoint = 15;
};