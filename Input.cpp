#include "Input.h"

#include "World.h"

std::shared_ptr<sf::RenderWindow> Input::m_window = std::shared_ptr<sf::RenderWindow>();

bool Input::m_click = false;
bool Input::m_lClick = false;
bool Input::m_rClick = false;

void Input::Update()
{
	if (!m_window) {
		printf("ERROR: Window is missing in Input");
		return;
	}
	m_click = false;
	m_lClick = false;
	m_rClick = false;
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
			if (m_event.mouseButton.button == sf::Mouse::Left)
			{
				m_lClick = true;
			}
			else if(m_event.mouseButton.button == sf::Mouse::Right)
			{
				m_click = true;
			}
		}
	}
}