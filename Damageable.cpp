#include "Damageable.h"
#include "World.h"

std::vector<Damageable*> Damageable::all = std::vector<Damageable*>();

Damageable::Damageable()
{
}

Damageable::~Damageable()
{
}

void Damageable::draw()
{
	healthBarFill.setPosition(GAME_WINDOW_X + transform->rect.left, GAME_WINDOW_Y + transform->rect.top - 10);
	healthBarFill.setPosition(GAME_WINDOW_X + transform->rect.left, GAME_WINDOW_Y + transform->rect.top - 10);
	World::draw(healthBarFrame);
	World::draw(healthBarFill);
}

void Damageable::initHealthBar()
{
	healthBarFill.setSize({ 100, 20 });
	healthBarFrame.setSize({ 100, 20 });
	healthBarFill.setFillColor(sf::Color::Red);
	healthBarFrame.setFillColor(sf::Color::Black);
}
