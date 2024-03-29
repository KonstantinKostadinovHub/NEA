#pragma once

#include "defines.h"

#include <iostream>
#include "Input.h"

class Shape {
public:
    Shape() {}
    virtual ~Shape() {};

    SHAPE m_type;

    virtual void Draw() = 0;
    virtual void AddPoint(sf::Vector2f v) 
    {
        m_controlPoints.append(v);
        m_controlPoints[m_controlPoints.getVertexCount() - 1].color = sf::Color(255, 255, 255, 50);
        Recalculate();
        AdditionalCalculations();
    };
    virtual void SetPoint(size_t i, sf::Vector2f v, int flag = 0)
    {
        m_controlPoints[i].position = v;
        Recalculate();
        AdditionalCalculations();
    };
    virtual void DeletePoint(size_t index)
    {
        for (size_t i = index; i < m_controlPoints.getVertexCount() - 1; i++)
        {
            m_controlPoints[i] = m_controlPoints[i + 1];
        }
        m_controlPoints.resize(m_controlPoints.getVertexCount() - 1);
        Recalculate();
        AdditionalCalculations();
    };

    virtual std::pair<size_t, int> IsSelected() 
    {
        for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
        {
            if (inCircle(m_controlPoints[i].position, m_controlPointRadius, sf::Vector2f(Input::MouseCoor())))
            {
                return { i, 0 };
            }
        }
        return { size_t(-1), -1 };
    }

    sf::VertexArray GetVertexArray() const { return m_curve; }
    sf::VertexArray GetFirstDerivative() { return m_firstDerivative; }
    sf::VertexArray GetSecondDerivative() { return m_secondDerivative; }

    size_t GetControlPointsCount() { return m_controlPoints.getVertexCount(); }
    size_t GetPointsPerSection() { return m_samples; }

    static bool m_drawOsculatingCircleGraph;
protected:
    sf::VertexArray m_curve; 
    sf::VertexArray m_perp; 
    sf::VertexArray m_firstDerivative;
    sf::VertexArray m_secondDerivative;
    sf::VertexArray m_osculatingCircleRadiuses;

    sf::VertexArray m_controlPoints;
    sf::VertexArray m_curveToDraw;
    /*
    * size_t first - index of the point
    * int second - timestamp in ms when it was last drawn
    */
    std::pair<size_t, int> m_lastPointInfo;

    const size_t m_samples = 20;
    const size_t m_msPerPoint = 15;	
    const float m_controlPointRadius = 10;


    virtual void Recalculate() = 0;

    // used for draw animation
    void UpdateLastVisiblePoint();

    // Caclucalting functions
    void CDerivative(const sf::VertexArray& in, sf::VertexArray& out)
    {
        out.clear();
        for (size_t i = 0; (long long)i < (long long)(in.getVertexCount()) - 1ll; i++)
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
            for (size_t i = 0; i < m_secondDerivative.getVertexCount(); i++)
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
                float k = (m_firstDerivative[i].position.x * m_secondDerivative[i].position.y - m_firstDerivative[i].position.y * m_secondDerivative[i].position.x) / powf(magnitude(m_firstDerivative[i].position), 3.0f);
                m_osculatingCircleRadiuses.append(m_curve[i].position 
                    + m_perp[i].position * k * 1000.0f);
            }
        }
    }
    void AdditionalCalculations()
    {
        if (m_controlPoints.getVertexCount() > 1)
        {
            CDerivative(m_curve, m_firstDerivative);
            CDerivative(m_firstDerivative, m_secondDerivative);
            COsculatingRadiuses();
        }
    };
};
