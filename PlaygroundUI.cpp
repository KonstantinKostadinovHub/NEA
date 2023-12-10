#include "PlaygroundUI.h"

#include "World.h"
#include "defines.h"

SHAPE PlaygrounUI::m_selectedTool = SHAPE::NONE;

void PlaygrounUI::LoadTools()
{
	iTool _tool;
	
	_tool.m_name = "Line";
	_tool.m_enumCode = SHAPE::LINE;
	AddTool(_tool);

	_tool.m_name = "BezierCurve";
	_tool.m_enumCode = SHAPE::BEZIER_CURVE;
	AddTool(_tool);
	
	_tool.m_name = "BezierSpline";
	_tool.m_enumCode = SHAPE::BEZIER_SPLINE;
	AddTool(_tool);

	_tool.m_name = "Hermite";
	_tool.m_enumCode = SHAPE::HERMITE;
	AddTool(_tool);

	m_splineBarTx.loadFromFile(IMAGE_FOLDER + UI_FOLDER + "spline_bar.png");

	m_splineBarSp.setTexture(m_splineBarTx);
	m_splineBarSp.setPosition(720.0f, 27.0f);
}

void PlaygrounUI::AddTool(iTool t)
{
	ToolButton btn;
	m_tools.insert({ t.m_enumCode, btn });
	m_tools.at(t.m_enumCode).Init(IMAGE_FOLDER + UI_FOLDER + t.m_name + ".png");
}

void PlaygrounUI::Init()
{
	LoadTools();
}

void PlaygrounUI::Run()
{
	World::draw(m_splineBarSp);

	ImGui::SetNextWindowPos(ImVec2(714, 36));
	if (ImGui::Begin(" ", NULL, DEFAULT_WINDOW))
	{
		for (auto& itr : m_tools)
		{
			
			if (itr.second.Draw())
			{
				if (Input::IsKeyPressed(sf::Keyboard::LControl) || Input::IsKeyPressed(sf::Keyboard::RControl))
				{
					InfoCard::SetInfoCard(INFO_CARD(size_t(itr.first)));
				}
				else
				{
					m_selectedTool = itr.first;
				}
			}
		}
	}
	ImGui::End();
}