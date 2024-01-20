#pragma once

#include "Shape.h"

class BezierSpline : public Shape{
public:
	BezierSpline() {
		m_type = SHAPE::BEZIER_SPLINE;
		m_lastPointInfo = { 0, 0 };
	}
	virtual ~BezierSpline() { };
	BezierSpline(sf::Vector2f s)
	{
		m_type = SHAPE::BEZIER_SPLINE;
		m_controlPoints = sf::VertexArray(sf::Lines, 1);
		m_controlPoints[0].position = s;
		m_controlPoints[0].color = sf::Color(255, 255, 255, 50);
		m_curve = sf::VertexArray(sf::LineStrip, 1);
		m_curve[0].position = s;
		m_curveToDraw = sf::VertexArray(sf::LinesStrip, 1);
		m_curveToDraw[0].position = s;
		m_curveToDraw[0].color = sf::Color(255, 255, 255, 50);
	}

	void AddPoint(sf::Vector2f v)
	{
		sf::Vector2f cp1, cp2, knot = v, directionVector, lastPoint = m_controlPoints[m_controlPoints.getVertexCount() - 1].position, startToFinish = v - lastPoint;
		if (m_controlPoints.getVertexCount() > 1)
		{
			directionVector = lastPoint - m_controlPoints[m_controlPoints.getVertexCount() - 2].position;
		}
		else
		{
			directionVector = v - lastPoint;
		}
		
		cp1 = lastPoint + directionVector;
		cp2 = lastPoint + directionVector * 0.75f + startToFinish * 0.5f + normalize(sf::Vector2f(-directionVector.y, directionVector.x)) * 20.0f;
		
		m_controlPoints.append(cp1);
		m_controlPoints.append(cp2);
		m_controlPoints.append(knot);

		m_controlPoints[m_controlPoints.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
		Recalculate();
		AdditionalCalculations();
	}

	/*
	* flag = 0 -> normal
	* flag = 1 -> mirror
	*/
	void SetPoint(size_t i, sf::Vector2f v, int flag = 0)
	{
		if (i % 3 == 0)
		{
			sf::Vector2f displacement = v - m_controlPoints[i].position;
			m_controlPoints[i].position = v;
			if (i > 1)
			{
				m_controlPoints[i - 1].position += displacement;
			}
			if (i < m_controlPoints.getVertexCount() - 2 && i != 0)
			{
				m_controlPoints[i + 1].position += displacement;
			}
		}
		else
		{
			m_controlPoints[i].position = v;
			size_t indexToMirror = -1;
			size_t knotIndex = -1;
			if (flag == 1)
			{
				if (flag % 3 == 1 && i > 1)
				{
					indexToMirror = i - 2;
					knotIndex = i - 1;
				}
				else if(i + 2 < m_controlPoints.getVertexCount() - 1)
				{
					indexToMirror = i + 2;
					knotIndex = i + 1;
				}
			}
			if (indexToMirror != -1)
			{
				sf::Vector2f displacementFromKnot = v - m_controlPoints[knotIndex].position;
				m_controlPoints[indexToMirror].position = m_controlPoints[knotIndex].position -displacementFromKnot;
			}
		}
		Recalculate();
		AdditionalCalculations();
	}

	void DeletePoint(size_t index)
	{
		if (m_controlPoints.getVertexCount() == 1)
		{
			m_controlPoints.clear();
			return;
		}
		if (index % 3 == 0)
		{
			if (index != 0 && index != m_controlPoints.getVertexCount() - 1)
			{
				/* Explanation of why 'm_controlPoints.getVertexCount() - 4'
				* -1 - miss the last knot
				* -2 - miss the control point before it
				* -3 - must be deleted as the last knot will not need it
				*/
				
				for (size_t i = index; (long long)i < (long long)(m_controlPoints.getVertexCount()) - 3ll; i += 3)
				{
					m_controlPoints[i - 1] = m_controlPoints[i + 2];
					m_controlPoints[i] = m_controlPoints[i + 3];
					if (i < m_controlPoints.getVertexCount() - 4)
						m_controlPoints[i + 1] = m_controlPoints[i + 4];
				}
			}
			else if (index == 0)
			{
				for (size_t i = 0; i < m_controlPoints.getVertexCount() - 3; i ++)
				{
					m_controlPoints[i] = m_controlPoints[i + 3];
				}
			}
			
			m_controlPoints.resize(m_controlPoints.getVertexCount() - 3);

		}
		Recalculate();
		AdditionalCalculations();
	}

	void Draw() override;
	void DrawControlPoints();
private:
	void Recalculate() override;
	sf::Vector2f LerpRecursively(sf::VertexArray vertices, float t);
	void CalcSection(size_t i);

	const float m_pointCollisionBox = 10.0f;
	const float m_controlPointRadius = 5.0f;

};