#pragma once

#include <queue>

#include "defines.h"

class Agent {
public:
	Agent() { };
	virtual ~Agent() { };

	void Init(sf::VertexArray v) {
		m_agentTx.loadFromFile(IMAGE_FOLDER + UI_FOLDER + "agent.png");
		m_agentSp.setTexture(m_agentTx);
		QueuePath(v);
		m_agentSp.setPosition(
			{ v[0].position.x - m_agentTx.getSize().x, 
			v[0].position.y - m_agentTx.getSize().y});
	};

	bool Update();
	void Draw();

	void QueuePath(sf::VertexArray v) 
	{
		for (size_t i = 0; i < v.getVertexCount(); i++)
		{
			m_path.push(v[i].position);
		}
	};
private:
	// limit from 0.0 to 1.0
	static float m_speed;
	float m_currT = 0.0f;

	sf::Sprite m_agentSp;
	static sf::Texture m_agentTx;
	
	std::queue<sf::Vector2f> m_path;

	void Move();
};