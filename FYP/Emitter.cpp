#include "Emitter.h"

Emitter::Emitter()
{

}

Emitter::Emitter(float x, float y, sf::Color col)
{
	size = 15;
	for (int i = 0; i < size; i++)
	{
		Particle* p = new Particle(x, y, col);
		particles.push_back(p);
	}
}

void Emitter::Init()
{
	for each (Particle* p in particles)
	{
		//p->SetPosition(m_position);
	}
}

void Emitter::Update()
{
}

void Emitter::Update(sf::Vector2f target)
{
	for each (Particle* p in particles)
	{
		p->Update(target);
	}
}

void Emitter::Draw(sf::RenderWindow &win)
{
	for each (Particle* p in particles)
	{
		p->Draw(win);
	}
}

void Emitter::SetPosition(sf::Vector2f pos) 
{ 
	m_position = pos; 
}

void Emitter::SetAlive(bool b) 
{
	for each (Particle* p in particles)
	{
		p->SetAlive(b);
	}
}