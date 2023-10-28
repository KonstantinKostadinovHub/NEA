#pragma once

#include <vector>

#include "Input.h"
#include "defines.h"

#include "Button.h"

struct iTool {
	std::string m_name;
	SHAPE m_enumCode;
};

class ToolButton : public Button {
public:
	ToolButton() { m_framePadding = -1; m_size = { 43, 43}; }
	virtual ~ToolButton() {};

	virtual	bool Draw() {
		ImGui::SameLine();
		ImGui::Dummy(ImVec2(8, 0));
		ImGui::SameLine();
		return ImGui::ImageButton(m_sprite, m_size, m_framePadding, m_color, sf::Color::White);
	};
private:
};

class PlaygrounUI {
public:
	PlaygrounUI(){};
	virtual ~PlaygrounUI(){};
	
	void Init();
	void Run();

	static SHAPE GetSelected() { return m_selectedTool; };
private:
	void LoadTools();
	
	void AddTool(iTool t);

	std::map<SHAPE, ToolButton> m_tools;

	static SHAPE m_selectedTool;
	
	Input& m_inputManager = Input::GetInstance();
	
	sf::Texture m_splineBarTx;
	sf::Sprite m_splineBarSp;
};