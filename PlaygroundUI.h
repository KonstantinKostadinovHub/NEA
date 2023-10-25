#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <vector>

#include "Input.h"

enum class plTool {
	None = 0,
	Default = 1,
	Line = 2,
	BezierCurve = 3,
};

struct iTool {
	std::string m_name;
	plTool m_enumCode;
};

class ToolButton {
public:
	ToolButton() { m_framePadding = -1; m_size = { 43, 43}; }
	virtual ~ToolButton() {};

	void Init(std::string file) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		m_tex.loadFromFile(file); m_sprite.setTexture(m_tex);
	}
	bool Draw() {
		ImGui::SameLine();
		ImGui::Dummy(ImVec2(8, 0));
		ImGui::SameLine();
		return ImGui::ImageButton(m_sprite, m_size, m_framePadding, sf::Color(33, 30, 41, 255), sf::Color::White);
	};
private:
	sf::Sprite m_sprite;
	sf::Texture m_tex;
	sf::Vector2f m_size;
	int m_framePadding;
};

class PlaygrounUI {
public:
	PlaygrounUI(){};
	virtual ~PlaygrounUI(){};
	
	void Init();
	void Run();

	static plTool GetSelected() { return m_selectedTool; };
private:
	void LoadTools();
	
	void AddTool(iTool t);

	std::map<plTool, ToolButton> m_tools;

	static plTool m_selectedTool;
	
	Input& m_inputManager = Input::GetInstance();
	
	sf::Texture m_splineBarTx;
	sf::Sprite m_splineBarSp;
};