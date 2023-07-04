#include "Config.h"

#include "defines.h"

Config* Config::singleton = nullptr;

#include <iostream>

void Config::init()
{
	archerTower.init();
	kingTower.init();
	std::ifstream data(CONFIG_FOLDER + "archerTower.txt");
	load(archerTower, data);
	data.close();
	data.open(CONFIG_FOLDER + "kingTower.txt");
	load(kingTower, data);
	data.close();

	for (int i = 1; i < (int)CARD::SIZE; i++) {
		load((CARD)i);
	}
}

Config* Config::getInstance()
{
	if (singleton == nullptr) {
		singleton = new Config();
	}
	return singleton;
}

void Config::load(CARD card)
{
	Object obj;
	obj.setCard(card);
	
	std::string name = cardName(card);
	std::ifstream data(CONFIG_FOLDER + CARDS_FOLDER + name + ".txt");
	load(obj, data);
	data.close();
	
	cards.insert({ card, Object()});
	cards.at(card).copy(obj);
	cardsUI.insert({ card, sf::Texture() });
	if (!cardsUI.at(card).loadFromFile(IMAGE_FOLDER + CARDS_FOLDER + UI_FOLDER + name + ".png")) {
		printf("Error: image not found: ");
	}
}

void Config::load(Object& object, std::ifstream& data)
{
	int componentType = -1;

	Transform* transform = nullptr;
	Moving* moving = nullptr;
	Damageable* damageable = nullptr;
	Behaviour* behaviour = nullptr;

	while (!data.eof()) {
		data >> componentType;
		switch (componentType) {
			case (int)COMPONENT_TYPE::TRANSFORM:
				transform = dynamic_cast<Transform*>(object.addComponent(COMPONENT_TYPE::TRANSFORM));
				load(transform, data, object.getCard());
				break;
			case (int)COMPONENT_TYPE::MOVING:
				moving = dynamic_cast<Moving*>(object.addComponent(COMPONENT_TYPE::MOVING));
				load(moving, data);
				break;
			case (int)COMPONENT_TYPE::DAMAGEABLE:
				damageable = dynamic_cast<Damageable*>(object.addComponent(COMPONENT_TYPE::DAMAGEABLE));
				load(damageable, data);
				break;
			case (int)COMPONENT_TYPE::BEHAVIOUR:
				behaviour = dynamic_cast<Behaviour*>(object.addComponent(COMPONENT_TYPE::BEHAVIOUR));
				if (moving && transform) {
					load(behaviour, data);
				}
				else {
					printf("Error: Can't load behaviour component \n");
				}
				break;
			default:
				printf("Error: Invalid component type %d \n", componentType);
				break;
		}
	}
}

void Config::load(Transform* transform, std::ifstream& data, CARD card)
{
	sf::FloatRect rect;
	bool onGround, isBuilding;
	std::string image;
	data >> rect.width >> rect.height;
	data >> onGround >> isBuilding;
	std::string location;
	if (card == CARD::NONE) {
		data >> image;
		location = IMAGE_FOLDER + image;
	}
	else {
		location = IMAGE_FOLDER + cardName(card) + ".png";
	}
	transform->init(rect, onGround, isBuilding, location);
}

void Config::load(Moving* moving, std::ifstream& data)
{
	float speed;
	data >> speed;
	moving->init(speed);
}

void Config::load(Damageable* damageable, std::ifstream& data)
{
	float health;
	data >> health;
	damageable->init(health);
}

void Config::load(Behaviour* behaviour, std::ifstream& data)
{
	/*std::shared_ptr<Moving> m = std::make_shared<Moving>(moving);
	std::shared_ptr<Transform> t = std::make_shared<Transform>(transform);
	behaviour->init(m, t);*/
}
