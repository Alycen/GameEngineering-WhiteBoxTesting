#ifndef _NPC_BEAR_
#define _NPC_BEAR_

#include "stdafx.h"
#include "NPC_Critter.h"

#define DistanceOfNeck 60.5
#define DistanceOfTail -65

class Bear : public Critter
{
private:
	float m_speed = 3;
public:
	Bear();
	Bear(float, float);

	void Update();
	void Update(sf::Vector2f);
	void Draw(sf::RenderWindow&);

	// AI Behaviours
	void Move(); // Wander
	void Flee(sf::Vector2f);
	void Chase(sf::Vector2f);
	void Attack();
	void KeepDistance(sf::Vector2f);

	// Helper Methods for AI
	sf::Vector2f Closest(sf::Vector2f, sf::Vector2f);

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }

	Bear::~Bear() {};
};

#endif