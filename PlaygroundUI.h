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
	ToolButton() { m_framePadding = -1; m_size = { 30, 30}; }
	virtual ~ToolButton() {};

	void Init(std::string file) { m_tex.loadFromFile(file); m_sprite.setTexture(m_tex); }
	bool Draw() { ImGui::SameLine(); return ImGui::ImageButton(m_sprite, m_size, m_framePadding); };
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
};