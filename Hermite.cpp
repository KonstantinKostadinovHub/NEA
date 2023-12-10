#include "Hermite.h"

#include "defines.h"

#include "World.h"

void Hermite::Draw()
{
    UpdateLastVisiblePoint();
    World::draw(m_curveToDraw);
    //World::draw(m_controlPoints);
    for (size_t i = 0; i < m_controlPoints.getVertexCount(); i++)
    {
        auto circle = sf::CircleShape(m_controlPointRadius, 10);
        circle.setPosition(m_controlPoints[i].position - sf::Vector2f(m_controlPointRadius, m_controlPointRadius));
        World::draw(circle);
    }

    if (m_drawOsculatingCircleGraph)
    {
        if (m_osculatingCircleRadiuses.getVertexCount() == 0) COsculatingRadiuses();
        World::draw(m_osculatingCircleRadiuses);
    }
}

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
    m_curve.append(m_controlPoints[0].position);
    if (m_controlPoints.getVertexCount() > 2)
    {
        const size_t controlPointsCount = m_controlPoints.getVertexCount();
        CalcSection(0);

        for (size_t i = 2; i < controlPointsCount - 2; i+=2)
        {
            CalcSection(i);
        }
    }
}

void Hermite::CalcSection(size_t i)
{
    sf::VertexArray section;
    for (size_t j = 0; j < 4; j++)
    {
        section.append(m_controlPoints[i + j].position);
    }

    for (size_t j = 0; j <= m_samples; j++)
    {
        m_curve.append(LerpRecursively(section, 1.0f * j / m_samples));
    }

    m_curve.append(section[2]);
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
        sf::Vector2f m0 = (tCubed - 2.0f * tSquared + t) * vertices[1].position;
        sf::Vector2f m1 = (tCubed - tSquared) * vertices[3].position;
        
        res = p0 + p1 + m0 + m1;
    }
    else
    {
        printf("FATAL ERROR: Hermite::LerpRecusively() not enough vertecies");
    }
    return res;
}
