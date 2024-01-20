#pragma once

#include "Shape.h"

class Hermite : public Shape {
public:
	Hermite() {
		m_type = SHAPE::HERMITE;
		m_lastPointInfo = { 0, 0 };
	}

	virtual ~Hermite() {};
	Hermite(sf::Vector2f s) {
		m_type = SHAPE::HERMITE;

		m_controlPoints = sf::VertexArray(sf::LineStrip, 0);
		m_controlPoints.append(s);
		m_controlPoints.append(sf::Vector2f{ s.x, s.y + m_defaultVelocityAtPoint });
		m_controlPoints[0].position = s;
		m_controlPoints[0].color = sf::Color(255, 255, 255, 50);
		
		m_curve = sf::VertexArray(sf::Lines, 1);
		m_curve[0].position = s;
		
		m_curveToDraw = sf::VertexArray(sf::LinesStrip, 1);
		m_curveToDraw[0].position = s;
		m_curveToDraw[0].color = sf::Color(255, 255, 255, 50);
	}

	void AddPoint(sf::Vector2f v)
	{
		// because the last point is not an actual point, rather a velocity vector
		sf::Vector2f lastPoint = m_controlPoints[m_controlPoints.getVertexCount() - 2].position;
		sf::Vector2f velocityAtPoint = { v - lastPoint};

		m_controlPoints.append(v);
		m_controlPoints.append(v + normalize(velocityAtPoint) * m_defaultVelocityAtPoint);
		
		Recalculate();
		AdditionalCalculations();
	}

	void SetPoint(size_t i, sf::Vector2f v, int flag = 0)
	{
		if (i % 2 == 0)
		{
			sf::Vector2f displacement = v - m_controlPoints[i].position;
			m_controlPoints[i].position = v;
			
			m_controlPoints[i + 1].position += displacement;
		}
		else
		{
			m_controlPoints[i].position = v;
		}
		Recalculate();
		if(m_controlPoints.getVertexCount() > 2)	AdditionalCalculations();
	}

	void DeletePoint(size_t index)
	{
		if (m_controlPoints.getVertexCount() <= 2)
		{
			m_controlPoints.clear();
			return;
		}
		if (index % 2 == 0)
		{
			for (size_t i = index; (long long)i < (long long)(m_controlPoints.getVertexCount()) - 2ll; i += 3)
			{
				m_controlPoints[i] = m_controlPoints[i + 2];
				m_controlPoints[i + 1] = m_controlPoints[i + 3];
			}
			m_controlPoints.resize(m_controlPoints.getVertexCount() - 2);

		}
		Recalculate();
		AdditionalCalculations();
	}

	void Draw() override;
	void DrawControlPointLines();
private:
	void Recalculate();
	void CalcSection(size_t i);
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);

	const float m_defaultVelocityAtPoint = 100.0f;

	sf::Color m_color;

private:
};