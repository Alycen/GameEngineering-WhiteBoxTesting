#ifndef _NPC_DEER_
#define _NPC_DEER_

#include "SFML\Graphics.hpp"

class Deer
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
	// Base Class for Stag and Doe

};

#endif