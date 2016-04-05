#ifndef _NPC_BEAR_
#define _NPC_BEAR_

#include "stdafx.h"
#include "Pvector.h"

#define DistanceOfNeck 60.5

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

	void Update();
	void Draw(sf::RenderWindow&);
	void Move();

	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }

	Bear::~Bear() {};

	Pvector m_pvecPosition;
};

#endif