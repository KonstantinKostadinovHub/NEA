#include "Game.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <iostream>
#include "World.h"

std::shared_ptr<Config> Game::config = std::shared_ptr<Config>();

Game::Game()
{

}

Game::~Game()
{
}

void Game::Init()
{
	config.reset(Config::getInstance());

	m_background = sf::RectangleShape(sf::Vector2f(1920, 1080));
	m_background.setFillColor(sf::Color(9, 6, 25));
	m_background.setPosition(0, 0);
	
	config->init();

	m_ui.Init();
}

void Game::Run()
{
	Update();
	m_ui.Run();
	Draw();
}


void Game::Update()
{
	if (m_ui.GetSelected() != plTool::None && Input::IsMousePressed(mouseBtn::lClick)) {
		m_geometryManager.Update();
	}
}

void Game::Draw()
{
	World::draw(m_background);

	m_geometryManager.Draw();
}
