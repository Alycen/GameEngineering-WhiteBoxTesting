#ifndef _EMITTER_
#define _EMITTER_

#include "Particle.h"
#include <list>

class Emitter
{
private:
	std::list<Particle*> particles;
	sf::Vector2f m_position;
	int size;
public:
	Emitter();
	Emitter(float, float, sf::Color);

	void Update();
	void Update(sf::Vector2f);
	void Draw(sf::RenderWindow&);

	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	void SetAlive(bool);
};

#endif