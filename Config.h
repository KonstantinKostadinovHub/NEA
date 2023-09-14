#pragma once

#include <unordered_map>
#include <fstream>

class Config {
public:
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

	void init();

	static Config* getInstance();
private:
	Config() {};

	static Config* singleton;
};
