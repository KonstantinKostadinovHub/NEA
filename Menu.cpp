#include "Menu.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "World.h"

GAME_MODE Menu::gameMode = GAME_MODE::PLAYER;

Menu::Menu()
{
}

void Menu::init()
{
}

void Menu::run()
{
	update();
	draw();
}

GAME_MODE Menu::getGameMode()
{
    return gameMode;
}

void Menu::update()
{
	ImGui::Text("Choose the game mode");
	const char* items[] = { "Player", "AI", "Training" };
	if (ImGui::Combo("Options", &selectedModeIndex, items, IM_ARRAYSIZE(items))) {
		printf("%d", selectedModeIndex);
	}
	if (ImGui::Button("Continue", ImVec2(200, 20))) {
		World::setState(STATE(selectedModeIndex + 2));
	}
}

void Menu::draw()
{
    	
}
