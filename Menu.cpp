#include "Menu.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "World.h"

SCENE Menu::scene = SCENE::MENU;

Menu::Menu()
{
}

void Menu::Init()
{
}

void Menu::Run()
{
	Update();
	Draw();
}

SCENE Menu::getScene()
{
    return scene;
}

void Menu::Update()
{
	ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);
	ImGui::Text("Choose the game mode");
	const char* items[] = { "PLAYGROUND" };
	if (ImGui::Combo("Options", &selectedModeIndex, items, IM_ARRAYSIZE(items))) {
		printf("%d", selectedModeIndex);
	}
	if (ImGui::Button("Continue", ImVec2(200, 20))) {
		World::setState(SCENE(selectedModeIndex + 2));
	}
	ImGui::End();
}

void Menu::Draw()
{
    	
}
