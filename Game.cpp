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

void Game::init()
{
	config.reset(Config::getInstance());

	background = sf::RectangleShape(sf::Vector2f(608, 1080));
	background.setFillColor(sf::Color(255, 255, 255));
	background.setPosition(656, 0);
	
	config->init();
}

void Game::run()
{
	update();
	draw();
}


void Game::update()
{
}

void Game::draw()
{
	World::draw(background);
	
}
