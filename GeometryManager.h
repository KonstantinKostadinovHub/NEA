#pragma once

#include "Line.h"
#include "ControlPointArray.h"

#include "StatsUI.h"
#include "InfoCard.h"

#include "Agent.h"

class GeometryManager {
public:
    std::vector<std::shared_ptr<Shape>> m_shapes;

    static GeometryManager& GetInstance() {
        static GeometryManager instance; // Guaranteed to be destroyed once
        return instance;
    }

    void Init() { m_statsUI.Init(); m_infoCard.Init(); };

    void Update();
    void RemoveLastShape();

    void Draw();

    std::pair<size_t, int> CheckForSelection(sf::Vector2f mousePos);
private:
    GeometryManager() { m_selectedIndex = size_t(-1); };
    
    // Private copy constructor and assignment operator to prevent copying
    GeometryManager(const GeometryManager&) = delete;
    GeometryManager& operator=(const GeometryManager&) = delete;

    void CreatePoint();

    void ShowStats();
    void CreateAgent(const sf::VertexArray& v);

    bool OverlapUI();

    StatsUI m_statsUI;
    InfoCard m_infoCard;

    std::shared_ptr<Shape> m_lastShape;
    std::vector<Agent> m_agents;
    size_t m_selectedIndex;
    int m_selectionFlag;
};