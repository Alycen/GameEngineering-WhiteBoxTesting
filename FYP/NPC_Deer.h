#ifndef _NPC_DEER_
#define _NPC_DEER_

#include "SFML\Graphics.hpp"

class Deer
{
protected:
	sf::Texture m_bodyTexture;
	sf::Texture m_headTexture;
	sf::Sprite m_bodySprite;
	sf::Sprite m_headSprite;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	float m_speed;
	float m_rotation;

	float m_attackDamage;
	float m_health;
public:
	Deer::Deer() { }
	Deer::~Deer() { }

	virtual void Deer::Update() 
	{

	}
	virtual void Deer::Update(sf::Vector2f target) 
	{

	}
	virtual void Deer::Draw(sf::RenderWindow &win)
	{
		win.draw(m_bodySprite);
		win.draw(m_headSprite);
	}

	// AI Behaviour
	virtual void Move()
	{

	}
	virtual void Flee(sf::Vector2f target)
	{

	}
	virtual void Chase(sf::Vector2f target)
	{

	}
	virtual void Attack()
	{

	}
	virtual void KeepDistance(sf::Vector2f target)
	{

	}

	//
	sf::Vector2f Closest(sf::Vector2f pos, sf::Vector2f target)
	{
		float dx = pos.x - target.x, dy = pos.y - target.y, x = target.x, y = target.y;
		if (abs(dx) > 1200 && dx != 0)
		{
			x = target.x + 2400 * (dx / abs(dx));
		}
		if (abs(dy) > 900 && dy != 0)
		{
			y = target.y + 1800 * (dy / abs(dy));
		}
		return sf::Vector2f(x, y);
	}

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }
};

#endif