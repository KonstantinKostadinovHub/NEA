#pragma once

#include "Button.h"

#include <vector>

enum class STAT {
	NONE = 0,
	FIRST_DERIVATIVE = 1,
	SECOND_DERIVATIVE = 2,
	OSCULATING_CIRCLE = 3,
	PERPENDICULARS = 4,
	CONTROL_POINT_GRAPH = 5,
	COUNT = 6
};

class StatsUI {
public:
	StatsUI() { m_selected = STAT::NONE; };
	virtual ~StatsUI() { };

	std::vector<std::pair<STAT, Button>> m_buttons;

	void AddButton(size_t);

	void Init();
	void Run();

	STAT GetSelected() { return m_selected; };
private:
	STAT m_selected;

	sf::Texture m_statsBarTx;
	sf::Sprite m_statsBarSp;
};