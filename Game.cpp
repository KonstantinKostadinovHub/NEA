#include "Game.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <iostream>
#include "World.h"

std::vector<std::unique_ptr<Object>> Game::objects = std::vector<std::unique_ptr<Object>>();
Config* Game::config = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(GAME_MODE _mode)
{
	config = Config::getInstance();

	mode = _mode;
	background.reset(new sf::RectangleShape(sf::Vector2f(608, 1080)));
	background->setFillColor(sf::Color(255, 255, 255));
	background->setPosition(656, 0);
	arena = sf::RectangleShape(sf::Vector2f(608, 1080));
	arena.setFillColor(sf::Color(0, 150, 0));
	arena.setPosition({ GAME_WINDOW_X, GAME_WINDOW_Y });
	arena.setSize({ GAME_WINDOW_W, GAME_WINDOW_H });
	
	config->init();
	initTowers();
	
	//TODO: proper intialization
	hand.init({ CARD::BALLOON, CARD::DRAGON, CARD::FIREBALL, CARD::GIANT, CARD::KNIGHT, CARD::PIGEONS, CARD::SKELETONS, CARD::WIZARD });
}

void Game::run()
{
	update();
	draw();
}

void Game::addObj(sf::Vector2i v, CARD c, int team)
{
	if (config) {
		std::unique_ptr<Object> obj = std::make_unique<Object>();
		obj.get()->copy(config->cards.at(c));
		obj.get()->setPos({ (float)(v.x - GAME_WINDOW_X), (float)(v.y - GAME_WINDOW_Y) });
		obj.get()->setTeam(team);
		objects.push_back(std::move(obj));
	}
	else {
		printf("Error: config used before it was initialised in Game");
	}
}

void Game::initTowers()
{
	std::unique_ptr<Object> _atrl = std::make_unique<Object>();
	_atrl.get()->copy(config->archerTower);
	std::unique_ptr<Object> _atrr = std::make_unique<Object>();
	_atrr.get()->copy(config->archerTower);
	std::unique_ptr<Object> _ktr = std::make_unique<Object>();
	_ktr.get()->copy(config->kingTower);
	std::unique_ptr<Object> _atbl = std::make_unique<Object>();
	_atbl.get()->copy(config->archerTower);
	std::unique_ptr<Object> _atbr = std::make_unique<Object>();
	_atbr.get()->copy(config->archerTower);
	std::unique_ptr<Object> _ktb = std::make_unique<Object>();
	_ktb.get()->copy(config->kingTower);

	_atrl.get()->setPos({ 68, 70 });
	_atrr.get()->setPos({ 384, 70});
	_ktr.get()->setPos({ 207, 0});
	_atbl.get()->setPos({ 68, 512 });
	_atbr.get()->setPos({ 384, 512 });
	_ktb.get()->setPos({ 207, 625 });

	_atrl->setTeam(2);
	_atrr->setTeam(2);
	_ktr->setTeam(2);
	_atbl->setTeam(1);
	_atbr->setTeam(1);
	_ktb->setTeam(1);

	objects.push_back(std::move(_atrl));
	objects.push_back(std::move(_atrr));
	objects.push_back(std::move(_ktr));
	objects.push_back(std::move(_atbl));
	objects.push_back(std::move(_atbr));
	objects.push_back(std::move(_ktb));
}

void Game::update()
{
	for (auto& object : objects) {
		object->action();
	}

	hand.update();
}

void Game::draw()
{
	World::draw(*background);
	World::draw(arena);

	for (const auto& object : objects) {
		object->draw();
	}

	hand.draw();
}
