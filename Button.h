#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "SFML/Graphics.hpp"

class Button {
public:
	Button() { m_size = { 40, 40 }; }
	Button(float size) { m_size = { size, size }; }
	Button(float x, float y) { m_size = { x, y }; }

	virtual ~Button() {};

	void Init(std::string file)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		m_tex.loadFromFile(file); m_sprite.setTexture(m_tex);
	}

	void SetColor(sf::Color c) { m_color = c; }
	void SetSameLine(bool v) { m_sameLine = v; }
	void SetDummy(ImVec2 v) { m_dummy = v; }

	virtual bool Draw() {
		if (m_sameLine) { ImGui::SameLine(); };
		ImGui::Dummy(m_dummy);
		return ImGui::ImageButton(m_sprite, m_size, m_framePadding, m_color, sf::Color::White);
	};
protected:
	sf::Sprite m_sprite;
	sf::Texture m_tex;
	sf::Vector2f m_size;
	int m_framePadding = -1;;
	sf::Color m_color = sf::Color(33, 30, 41, 255);
	ImVec2 m_dummy = ImVec2(0, 0);
	bool m_sameLine = true;
};