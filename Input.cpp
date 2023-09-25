#include "Input.h"

#include "World.h"

std::shared_ptr<sf::RenderWindow> Input::m_window = std::shared_ptr<sf::RenderWindow>();

bool Input::m_click = false;
bool Input::m_lClick = false;
bool Input::m_rClick = false;
bool Input::m_onClick = false;
bool Input::m_onLClick = false;
bool Input::m_onRClick = false;

void Input::Update()
{
	if (!m_window) {
		printf("ERROR: Window is missing in Input");
		return;
	}
	m_onClick = false;
	m_onLClick = false;
	m_onRClick = false;
	while (m_window->pollEvent(m_event)) 
	{
		ImGui::SFML::ProcessEvent(m_event);
		if (m_event.type == sf::Event::Closed)
		{
			m_window->close();
		}
		else if (m_event.type == sf::Event::MouseButtonPressed)
		{
			m_click = true;
			m_onClick = true;
			if (m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_lClick = true;
				m_onLClick = true;
			}
			else if(m_event.mouseButton.button == sf::Mouse::Right)
			{
				m_rClick = true;
				m_onRClick = true;
			}
		}
		else if (m_event.type == sf::Event::MouseButtonReleased)
		{
			m_click = false;
			if (m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_lClick = false;
			}
			else if (m_event.mouseButton.button == sf::Mouse::Right)
			{
				m_click = false;
			}
		}
	}
}