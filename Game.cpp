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

	m_background.Init();
	
	config->init();

	m_ui.Init();

}

void Game::Run()
{
	Update();
	Draw();
	m_ui.Run();
}


void Game::Update()
{
	m_geometryManager.Update();
}

void Game::Draw()
{
	m_background.Draw();

	m_geometryManager.Draw();
}
