#pragma once

#include <memory>

class Shape {
public:
    Shape() {}
    virtual ~Shape() {};

    virtual void Draw() = 0;
    virtual void AddPoint(sf::Vector2f e) = 0;
    virtual void SetPoint(size_t index, sf::Vector2f e, int flag = 0) = 0;
    virtual std::pair<size_t, int> IsSelected() const = 0;
};