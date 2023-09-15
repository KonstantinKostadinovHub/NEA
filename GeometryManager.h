#pragma once

#include "Line.h"

#include <memory>

class GeometryManager {
public:
    std::vector<std::shared_ptr<Shape>> m_shapes;

    static GeometryManager& GetInstance() {
        static GeometryManager instance; // Guaranteed to be destroyed once
        return instance;
    }

    void Update();
    void RemoveShape(size_t index);

    void Draw();
private:
	GeometryManager(){};

    void AddShape(std::shared_ptr<Shape> shape);
    
    // Private copy constructor and assignment operator to prevent copying
    GeometryManager(const GeometryManager&) = delete;
    GeometryManager& operator=(const GeometryManager&) = delete;

    std::shared_ptr<Shape> m_lastShape;
};