#pragma once

#include "defines.h"

class Menu {
public:
	Menu();

	void Init();

	void Run();

	static SCENE getScene();
private:
	void Update();
	void Draw();

	int selectedModeIndex = 0;
	sf::Texture m_tex;
	sf::RectangleShape m_menuSprite;
	static SCENE scene;
};