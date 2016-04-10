#ifndef _NPC_RABBIT_
#define _NPC_RABBIT_

#include "SFML\Graphics.hpp"
#include "NPC_Critter.h"

#define DistanceOfNeck 22

class Rabbit : public Critter
{
private:

public:
	Rabbit();
	Rabbit(float, float);
};

#endif 