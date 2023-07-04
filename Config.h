#pragma once

#include <unordered_map>
#include <fstream>

#include "Object.h"


class Config {
public:
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

	void init();

	static Config* getInstance();

	Object archerTower;
	Object kingTower;
	Object knight;

	std::unordered_map<CARD, Object> cards;
	std::unordered_map<CARD, sf::Texture> cardsUI;
private:
	Config() {};

	static Config* singleton;

	void load(CARD card);
	void load(Object& object, std::ifstream& data);

	void load(Transform* transform, std::ifstream& data, CARD card);
	void load(Moving* moving, std::ifstream& data);
	void load(Damageable* damageable, std::ifstream& data);
	void load(Behaviour* behaviour, std::ifstream& data);
};
