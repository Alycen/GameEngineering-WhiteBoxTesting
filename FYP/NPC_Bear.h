#ifndef _NPC_BEAR_
#define _NPC_BEAR_

#include "stdafx.h"

class Bear
{
private:
	sf::Texture m_bodyTexture;
	sf::Texture m_headTexture;
	sf::Sprite m_bodySprite;
	sf::Sprite m_headSprite;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	float m_rotation;
public:
	Bear();
	Bear(float, float);

	~Bear();
};

#endif