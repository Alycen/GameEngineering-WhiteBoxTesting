#ifndef _NPC_RABBIT_
#define _NPC_RABBIT_

#include "SFML\Graphics.hpp"
#include "NPC_Critter.h"

#define DistanceOfNeck 22
#define DistanceOfTail -20

class Rabbit : public Critter
{
private:
	float m_speed = 25.0f;
public:
	Rabbit();
	Rabbit(float, float);
	void Update(sf::Vector2f);
	void Flee(sf::Vector2f);
	void Move();
};

#endif 