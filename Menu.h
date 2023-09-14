#pragma once

#include "defines.h"

class Menu {
public:
	Menu();

	void init();

	void run();

	static SCENE getScene();
private:
	void update();
	void draw();

	int selectedModeIndex = 0;
	static SCENE scene;
};