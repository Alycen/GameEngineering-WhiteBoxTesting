#ifndef _NPC_KANINE_
#define _NPC_KANINE_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "NPC_Critter.h"

#define DistanceOfNeck 35.5
#define DistanceOfTail -35
#define DistanceOfAttack 105

class Kanine : public Critter
{
private:
	float m_speed = 3;
public:
	Kanine();
	Kanine(float, float);

	void Update();
	void Update(sf::Vector2f);
	void Draw(sf::RenderWindow&);
	
	// AI Behaviours
	void Move();
	void Chase(sf::Vector2f);
	void Flee(sf::Vector2f);

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }

	Kanine::~Kanine() {};
};

#endif