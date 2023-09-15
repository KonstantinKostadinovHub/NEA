#pragma once

#include "SFML/Graphics.hpp"
#include <memory>

enum class mouseBtn {
	click = 0,
	lClick = 1,
	rClick = 2
};

class Input {
public:
	static void Init(std::shared_ptr<sf::RenderWindow> window) { m_window = window; };

	// Function to get the instance of the InputManager
	static Input& GetInstance() {
		static Input instance; // Guaranteed to be destroyed once
		return instance;
	}

	void Update();

	static bool IsMousePressed(mouseBtn btn) 
	{ 
		switch (btn)
		{
		case mouseBtn::click:
			return m_click;
			break;
		case mouseBtn::lClick:
			return m_lClick;
			break;
		case mouseBtn::rClick:
			return m_rClick;
			break;
		default:
			break;
		}
	};
	static sf::Vector2i MouseCoor() { return m_window ? sf::Mouse::getPosition(*m_window) : sf::Vector2i(0, 0); }
private:
	static bool m_click;
	static bool m_lClick;
	static bool m_rClick;
	static std::shared_ptr<sf::RenderWindow> m_window;

	sf::Event m_event;
	// Private constructor to prevent external instantiation
	Input() {}
};