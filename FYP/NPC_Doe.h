#ifndef _NPC_DOE_
#define _NPC_DOE_

#include "NPC_Critter.h"

#define DistanceOfNeck 40

class Doe : public Critter
{
private:

public:
	Doe();
	Doe(float, float);
	void Update(sf::Vector2f);
	void Flee(sf::Vector2f);
	void Move();
};

#endif