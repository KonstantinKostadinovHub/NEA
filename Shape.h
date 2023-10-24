#pragma once

#include "defines.h"

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
        m_osculatingCircleRadiuses = sf::VertexArray(sf::Lines);
        m_osculatingCircleRadiuses.clear();
        CPerp();
        for (size_t i = 2; i < m_secondDerivative.getVertexCount(); i++)
        {
            m_osculatingCircleRadiuses.append(m_curve[i].position);
            // TODO find the size of the vector
            // Multiply it by the perp vector
            m_osculatingCircleRadiuses.append(m_curve[i].position + m_perp[i].position * magnitude(m_firstDerivative[i].position) / magnitude(m_secondDerivative[i - 1].position));
        }
    }
};