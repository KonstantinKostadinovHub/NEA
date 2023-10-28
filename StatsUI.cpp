#include "StatsUI.h"

#include "World.h"

void StatsUI::AddButton(size_t i)
{
	Button btn(32.0f);
	m_buttons.push_back(std::pair<STAT, Button>(static_cast<STAT>(i), btn));

	m_buttons[m_buttons.size() - 1].second.Init(IMAGE_FOLDER + UI_FOLDER + "stats_" + std::to_string(i) + ".png");
	m_buttons[m_buttons.size() - 1].second.SetSameLine(false);
	m_buttons[m_buttons.size() - 1].second.SetDummy(ImVec2(0, 20));
}

void StatsUI::Init()
{
	m_buttons.resize(size_t(STAT::COUNT) * 2);

	m_statsBarTx.loadFromFile(IMAGE_FOLDER + UI_FOLDER + "stats_bar.png");

	m_statsBarSp.setTexture(m_statsBarTx);
	m_statsBarSp.setPosition(19.0f, 77.0f);

	for (size_t i = 1; i < size_t(STAT::COUNT); i++)
	{
		AddButton(i);
	}
}

void StatsUI::Run()
{
	World::draw(m_statsBarSp);

	ImGui::SetNextWindowPos(ImVec2(27, 80));
	if (ImGui::Begin("STATS", NULL, DEFAULT_WINDOW))
	{
		for (auto& button : m_buttons)
		{
			if (button.second.Draw())
			{
				if (m_selected == button.first)
				{
					m_selected = STAT::NONE;
					break;
				}
				m_selected = button.first;
				break;
			}
		}
	}
	ImGui::End();
}