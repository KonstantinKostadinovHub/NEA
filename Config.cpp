#include "Config.h"

#include "defines.h"

Config* Config::singleton = nullptr;

#include <iostream>

void Config::init()
{}

Config* Config::getInstance()
{
	if (singleton == nullptr) {
		singleton = new Config();
	}
	return singleton;
}