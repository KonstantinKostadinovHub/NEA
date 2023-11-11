#include "Agent.h"

#include "World.h"

float Agent::m_speed			= 0.1f;
sf::Texture Agent::m_agentTx	= sf::Texture();

bool Agent::Update()
{
	Move();
	return !m_path.empty();
}

void Agent::Draw()
{
	m_agentSp.setTexture(m_agentTx);
	World::draw(m_agentSp);
}

void Agent::Move()
{
	if (!m_path.empty())
	{
		sf::Vector2f movementVector = m_path.front() - m_agentSp.getPosition()
			- sf::Vector2f({
				float(m_agentTx.getSize().x),
				float(m_agentTx.getSize().y) }) / 2.0f;
		m_agentSp.setRotation(angleFromVector(movementVector) / PI * 180.0f + 90.0f);

		m_agentSp.move(m_speed * movementVector);
			

		m_currT += m_speed;

		if (m_currT > 1.0f)
		{
			m_path.pop();
			m_currT = 0.0f;
		}
	}
}
