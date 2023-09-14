#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <vector>

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
	ToolButton() { m_framePadding = -1; };
	virtual ~ToolButton() {};

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
private:
	void LoadTools();
	
	void AddTool(iTool t);

	std::vector<iTool> m_tools;

	plTool m_selectedTool;
};