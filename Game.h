#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

#include "defines.h"

#include "Config.h"
#include "PlaygroundUI.h"
#include "GeometryManager.h"

class Game {
public:
	Game();
	~Game();

	void Init();

	void Run();
	PlaygrounUI m_ui;

private:
	void Update();
	void Draw();

	static std::shared_ptr<Config> config;

	sf::RectangleShape m_background;
	GeometryManager& m_geometryManager = GeometryManager::GetInstance();
};