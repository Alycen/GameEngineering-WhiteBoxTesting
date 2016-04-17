#ifndef _NPC_STAG_
#define _NPC_STAG_

#include "NPC_Critter.h"

#define DistanceOfNeck 58
#define DistanceOfTail -55

class Stag : public Critter
{
private:
	float m_speed = 5.0f;
public:
	Stag();
	Stag(float, float);
	void Update(sf::Vector2f);
	void Move();
};

#endif