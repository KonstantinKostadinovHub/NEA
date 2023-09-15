#include "PlaygroundUI.h"

#include "defines.h"

plTool PlaygrounUI::m_selectedTool = plTool::None;

void PlaygrounUI::LoadTools()
{
	iTool _tool;
	_tool.m_name = "Line";
	_tool.m_enumCode = plTool::Line;
	AddTool(_tool);
}

void PlaygrounUI::AddTool(iTool t)
{
	sf::Texture tex;
	if (tex.loadFromFile(IMAGE_FOLDER + UI_FOLDER + t.m_name + ".png")) {
		printf("Error: image not found: ");
		printf(t.m_name.c_str());
	}

	sf::Sprite sprite;
	sprite.setTexture(tex);

	ToolButton btn;
	btn.Init(sprite);
	m_tools.insert({ t.m_enumCode, btn });
}

void PlaygrounUI::Init()
{
	LoadTools();
}

void PlaygrounUI::Run()
{
	for (auto itr = m_tools.begin(); itr != m_tools.end(); itr++)
	{
		if (itr->second.Draw())
		{
			m_selectedTool = plTool::Line;
		}
	}
}