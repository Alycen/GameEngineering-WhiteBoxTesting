#ifndef _NPC_STAG_
#define _NPC_STAG_

#include "NPC_Critter.h"
#include <assert.h>

#define DistanceOfNeck 58
#define DistanceOfTail -55
#define DistanceOfAttack 120

class Stag : public Critter
{
private:
	float m_speed = 5.0f;
public:
	Stag();
	Stag(float, float);
	void Update(sf::Vector2f);
	void CheckStag(sf::Vector2f);
	void CheckStagUnitTest(sf::Vector2f);
	void Move();
	void Chase(sf::Vector2f);
	void Flee(sf::Vector2f);
	void Draw(sf::RenderWindow&);
};

#endif