#ifndef _PARTICLE_
#define _PARTICLE_

#include "SFML\Graphics.hpp"
#include "Collision.h"

class Particle
{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	float m_rotation;
	float m_speed;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Color m_colour;

	int ttl;
	float m_size;
	bool isAlive = true;
public:
	Particle();
	Particle(float, float, sf::Color);

	void Update();
	void Update(sf::Vector2f);
	void Draw(sf::RenderWindow&);

	void SetAlive(bool b) { isAlive = b; }
	void CheckCollision();
	sf::Vector2f Closest(sf::Vector2f, sf::Vector2f);

	~Particle();
};

#endif