#pragma once

#include "Transform.h"

class Damageable : public Component{
public:
	Damageable();
	virtual ~Damageable();

	static std::vector<Damageable*> all;

	std::shared_ptr<Transform> transform;
	int team;

	void init(float _health) { maxHealth = health; health = _health; initHealthBar(); };

	void setTeam(int t) { team = t; };
	void link(std::shared_ptr<Transform> _t) { transform = _t; all.push_back(this);};

	void action() override {};
	Damageable* clone() const override { return new Damageable(*this); }
	void takeDamage(int damage) { health -= damage; }
	// returns health as a value between 0 and 1
	double getHealth() { return health / maxHealth * 100.0f; }
	void draw();
private:
	float health;
	float maxHealth;
	sf::RectangleShape healthBarFrame;
	sf::RectangleShape healthBarFill;

	void initHealthBar();
};

