#pragma once

#include "defines.h"

#include <iostream>

class Shape {
public:
    Shape() {}
    virtual ~Shape() {};

    SHAPE m_type;

    virtual void Draw() = 0;
    virtual void AddPoint(sf::Vector2f e) = 0;
    virtual void SetPoint(size_t index, sf::Vector2f e, int flag = 0) = 0;
    virtual std::pair<size_t, int> IsSelected() const = 0;
    sf::VertexArray GetVertexArray() const { return m_curve; };
    virtual size_t GetPointsPerSection() const = 0;

    virtual size_t GetControlPointsCount() = 0;

    static bool m_drawOsculatingCircleGraph;
protected:
    sf::VertexArray m_curve; 
    sf::VertexArray m_perp; 
    sf::VertexArray m_firstDerivative;
    sf::VertexArray m_secondDerivative;
    sf::VertexArray m_osculatingCircleRadiuses;

    void CDerivative(const sf::VertexArray& in, sf::VertexArray& out)
    {
        out.clear();
        for (size_t i = 0; i < in.getVertexCount() - 1; i++)
        {
            out.append(sf::Vector2f(in[i + 1].position.x - in[i].position.x, in[i + 1].position.y - in[i].position.y));
        }
    }

    void CPerp() {
        m_perp.clear();
        m_perp = sf::VertexArray(sf::LinesStrip, 0);

        for (size_t i = 1; i < m_curve.getVertexCount(); i ++)
        {
            m_perp.append(
                sf::Vector2f(m_curve[i].position.y - m_curve[i - 1].position.y,
                    m_curve[i - 1].position.x - m_curve[i].position.x));
        }
    }

    void COsculatingRadiuses()
    {
        if (m_drawOsculatingCircleGraph)
        {
            m_osculatingCircleRadiuses = sf::VertexArray(sf::Lines);
            m_osculatingCircleRadiuses.clear();
            CPerp();
            for (size_t i = 2; i < m_secondDerivative.getVertexCount(); i++)
            {
                m_osculatingCircleRadiuses.append(m_curve[i].position);
                /*
                * Curvature K is found by:
                * using the determinant of the matrix
                * | fx sx |
                * | fy sy |
                * f is the first derivative and s is the second derivative
                *
                * and deviding it by the velocity (first derivative) vector cubed
                * 
                * | f | ^ 3
                * 
                */
                float k = (m_firstDerivative[i].position.x * m_secondDerivative[i].position.y - m_firstDerivative[i].position.y * m_secondDerivative[i].position.x) / magnitude(m_firstDerivative[i].position);
                m_osculatingCircleRadiuses.append(m_curve[i].position + m_perp[i].position * k / magnitude(m_firstDerivative[i].position) * 100.0f);
            }
        }
    }
};
