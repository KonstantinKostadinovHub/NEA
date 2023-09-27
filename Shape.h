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

    virtual size_t GetControlPointsCount() = 0;
};