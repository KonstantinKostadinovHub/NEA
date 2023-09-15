#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <vector>

#include "Input.h"

enum class plTool {
	None = 0,
	Line = 1
};

struct iTool {
	std::string m_name;
	plTool m_enumCode;
};

class ToolButton {
public:
	ToolButton() { m_framePadding = -1; m_size = { 100, 100 }; }
	virtual ~ToolButton() {};

	void Init(sf::Sprite sprite) { m_sprite = sprite; }
	bool Draw() { return ImGui::ImageButton(m_sprite, m_size, m_framePadding); };
private:
	sf::Sprite m_sprite;
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