#ifndef _EMITTER_
#define _EMITTER_

#include "Particle.h"
#include <list>
// if you use #include "Player.h" - causes strange issues

class Emitter
{
private:
	std::list<Particle*> particles;
	sf::Vector2f m_position;
	int size;
public:
	Emitter();
	Emitter(float, float, sf::Color);

	void Init();
	void Update();
	void Update(sf::Vector2f);
	void Draw(sf::RenderWindow&);

	void SetPosition(sf::Vector2f);
	void SetAlive(bool);
};

#endif