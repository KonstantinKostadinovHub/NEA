#pragma once

#include <map>
#include <memory>

#include "Behaviour.h"

enum class COMPONENT_TYPE {
	TRANSFORM = 0,
	DAMAGEABLE = 1,
	MOVING = 2,
	ATTACKING = 3,
	BEHAVIOUR = 4
};

class Object {
public:
	Object();
	void copy(Object& object) {
 		team = object.team;
		for (const auto& comp : object.components) {
			addComponent(comp.first, comp.second.get());
		}
		for (const auto& comp : object.components) {
			link(comp.first);
		}
	}

	Component* addComponent(COMPONENT_TYPE type);
	Component* addComponent(COMPONENT_TYPE type, Component* _comp);
	
	int team;

	std::weak_ptr<Transform> transform;

	void init();

	void draw(); 
	void action();

	void setPos(sf::Vector2f pos) {
		if (!transform.expired()) {
			transform.lock()->rect.left = pos.x;
			transform.lock()->rect.top = pos.y;
		}
		else { printf("FATAL ERROR: transform ptr expired"); }
	}

	void setTeam(int _team);
	void setCard(CARD c) { cardType = c; };
	CARD getCard() { return cardType; };

private:
	CARD cardType;
	std::map<COMPONENT_TYPE, std::shared_ptr<Component>> components;
	
	// every component should have the required pointers to other comps
	void link(COMPONENT_TYPE type);
};