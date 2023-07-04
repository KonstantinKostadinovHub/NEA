#pragma once

#include "defines.h"

class Menu {
public:
	Menu();

	void init();

	void run();

	static GAME_MODE getGameMode();
private:
	void update();
	void draw();

	int selectedModeIndex = 0;
	static GAME_MODE gameMode;
};