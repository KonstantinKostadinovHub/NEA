#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

#include "Transform.h"
#include "Damageable.h"

class Moving: public Component {
public:
	Moving() {};
	virtual ~Moving() {};
	
	void init(float _speed) {
		speed = _speed;
		stunDuration = 0;
	}

	// move towards the destination
	void action();

	Moving* clone() const override { return new Moving(*this); }
	void link(std::shared_ptr<Transform> t) { transform = t; };

	void setTeam(int _team) { team = _team; };

	std::weak_ptr<Transform> destination;
private:
	bool isStunned();
	int team;

	float speed;
	float stunDuration;

	sf::Time lastStun;

	std::weak_ptr<Transform> transform;
};