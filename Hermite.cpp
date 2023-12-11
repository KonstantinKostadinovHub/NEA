#include "Hermite.h"

#include "defines.h"

#include "World.h"

void Hermite::Draw()
{
    UpdateLastVisiblePoint();
    World::draw(m_curveToDraw);
    DrawControlPointLines();

    for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
    {
        auto circle = sf::CircleShape(m_controlPointRadius, 10);
        circle.setPosition(m_controlPoints[i].position - sf::Vector2f(m_controlPointRadius, m_controlPointRadius));
        
        if (i % 2 == 1)
        {
            circle.setFillColor(sf::Color(90, 90, 90, 255));
        }
        else
        {
            circle.setFillColor(sf::Color(255, 255, 255, 150));
        }
        World::draw(circle);
    }

    if (m_drawOsculatingCircleGraph)
    {
        if (m_osculatingCircleRadiuses.getVertexCount() == 0) COsculatingRadiuses();
        World::draw(m_osculatingCircleRadiuses);
    }
}

void Hermite::DrawControlPointLines()
{
    sf::VertexArray line = sf::VertexArray(sf::Lines, 0);
    for (size_t i = 0; i < m_controlPoints.getVertexCount(); i += 2)
    {
        line.clear();
        line.append(m_controlPoints[i]);
        line.append(m_controlPoints[i + 1]);
        line[0].color = sf::Color(255, 255, 255, 50);
        line[1].color = sf::Color(255, 255, 255, 50);
        World::draw(line);
    }
};

std::pair<size_t, int> Hermite::IsSelected() const
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

void Hermite::Recalculate()
{
    m_lastPointInfo.first = 0;
    m_curve.clear();
    const size_t controlPointsCount = m_controlPoints.getVertexCount();
    if (controlPointsCount > 2)
    {
        CalcSection(0);

        for (size_t i = 2; i < controlPointsCount - 2; i+=2)
        {
            CalcSection(i);
        }
        m_curve.append(m_controlPoints[controlPointsCount - 2]);
    }
    else 
    {
        m_curve.append(m_controlPoints[0]);
    }
}

void Hermite::CalcSection(size_t i)
{
    sf::VertexArray section;
    for (size_t j = 0; j < 4; j++)
    {
        section.append(m_controlPoints[i + j].position);
    }

    for (size_t j = 0; j < m_samples; j++)
    {
        m_curve.append(LerpRecursively(section, 1.0f * j / m_samples));
    }
}

// https://en.wikipedia.org/wiki/Cubic_Hermite_spline
sf::Vector2f Hermite::LerpRecursively(sf::VertexArray vertices, float t)
{
    float tCubed = powf(t, 3.0f);
    float tSquared = powf(t, 2.0f);
    sf::Vector2f res = vertices[0].position;
    if (vertices.getVertexCount() == 4)
    {
        sf::Vector2f p0 = (2.0f * tCubed - 3.0f * tSquared + 1.0f) * vertices[0].position;
        sf::Vector2f p1 = (-2.0f * tCubed + 3.0f * tSquared) * vertices[2].position;
        
        // The tangents are relatively calculated
        sf::Vector2f m0 = (tCubed - 2.0f * tSquared + t) * (vertices[1].position - vertices[0].position);
        sf::Vector2f m1 = (tCubed - tSquared) * (vertices[3].position - vertices[2].position);
        
        res = p0 + p1 + m0 + m1;
    }
    else
    {
        printf("FATAL ERROR: Hermite::LerpRecusively() not enough vertecies");
    }
    return res;
}
