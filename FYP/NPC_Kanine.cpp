#include "NPC_Kanine.h"

Kanine::Kanine() {}

Kanine::Kanine(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyKanineNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);
	
	m_headTexture.loadFromFile("Assets/Graphics/NPC/headKanineNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(20.0f, 40.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);
}

void Kanine::Update()
{
	m_bodySprite.setPosition(m_position.x, m_position.y);
	Move();
	m_pvecPosition.x = m_position.x;
	m_pvecPosition.y = m_position.y;
}

void Kanine::Draw(sf::RenderWindow &win)
{
	win.draw(m_bodySprite);
	win.draw(m_headSprite);
}

void Kanine::Move()
{

}