#include "Menu.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "World.h"

SCENE Menu::scene = SCENE::MENU;

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

SCENE Menu::getScene()
{
    return scene;
}

void Menu::update()
{
	ImGui::Text("Choose the game mode");
	const char* items[] = { "PLAYGROUND" };
	if (ImGui::Combo("Options", &selectedModeIndex, items, IM_ARRAYSIZE(items))) {
		printf("%d", selectedModeIndex);
	}
	if (ImGui::Button("Continue", ImVec2(200, 20))) {
		World::setState(SCENE(selectedModeIndex + 2));
	}
}

void Menu::draw()
{
    	
}
