#pragma once

class Shape {
public:
    Shape() {}
    virtual ~Shape() {};

    virtual void Draw() = 0;
    virtual void AddPoint(sf::Vector2f e) = 0;
};