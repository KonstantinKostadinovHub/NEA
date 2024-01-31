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
	if (!m_tex.loadFromFile(IMAGE_FOLDER + UI_FOLDER + "menu.png"))
	{
		printf("Texture not found for menu image");
	}
	m_menuSprite.setTexture(&m_tex);
	m_menuSprite.setSize({ 1920, 1080 });
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
	World::draw(m_menuSprite);
	if (Input::IsMousePressed(mouseBtn::click) && inCircle(sf::Vector2f(960, 540), 134, sf::Vector2f(Input::MouseCoor())))
	{
		World::setState(SCENE::PLAYGROUND);
	}
}

void Menu::Draw()
{
}
