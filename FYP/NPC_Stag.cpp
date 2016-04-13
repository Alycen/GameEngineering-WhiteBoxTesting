#include "NPC_Stag.h"

Stag::Stag() {}

Stag::Stag(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyStagNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);

	m_headTexture.loadFromFile("Assets/Graphics/NPC/headStagNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(60.0f, 45.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);
}