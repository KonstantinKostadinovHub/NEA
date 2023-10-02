#include "PlaygroundUI.h"

#include "defines.h"

plTool PlaygrounUI::m_selectedTool = plTool::None;

void PlaygrounUI::LoadTools()
{
	iTool _tool;
	
	_tool.m_name = "Line";
	_tool.m_enumCode = plTool::Line;
	AddTool(_tool);

	_tool.m_name = "BezierCurve";
	_tool.m_enumCode = plTool::BezierCurve;
	AddTool(_tool);
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
	ImGui::SetNextWindowPos(ImVec2(500, 0));
	if (ImGui::Begin(" ", NULL, DEFAULT_WINDOW))
	{
		for (auto& itr : m_tools)
		{
			if (itr.second.Draw())
			{
				m_selectedTool = itr.first;
			}
		}
	}
	ImGui::End();
}