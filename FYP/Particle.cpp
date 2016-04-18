#include "Particle.h"

Particle::Particle()
{
	m_texture.loadFromFile("Assets/Graphics/Effects/Particle.png");
	m_texture.setSmooth(true);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(5.0f, 5.0f);
	m_size = (rand() % 125 + 50) / 100.0f;

	ttl = rand() % 200 + 75;
}

Particle::Particle(float x, float y, sf::Color col)
{
	m_texture.loadFromFile("Assets/Graphics/Effects/Particle.png");
	m_texture.setSmooth(true);

	m_size = (rand() % 200 + 50) / 100.0f;

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(5.0f, 5.0f);
	m_sprite.setScale(m_size, m_size);

	ttl = rand() % 200 + 75;
	m_position = sf::Vector2f(x, y);
	m_colour = col;
}

void Particle::Update()
{

}

void Particle::Update(sf::Vector2f target)
{
	m_sprite.setPosition(m_position);

	target = Closest(m_position, target);
	sf::Vector2f diff = m_position - target;

	if (isAlive)
	{
		m_speed = rand() % 5 + 3;
		m_rotation = atan2(target.y - m_position.y, target.x - m_position.x);
		m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
		m_position += m_direction * m_speed;
	}
	if (diff.x*diff.x + diff.y*diff.y < 2000)
	{
		isAlive = false;
		//Reset Emitter
	}
}

void Particle::Draw(sf::RenderWindow &win)
{
	m_sprite.setColor(m_colour);
	if (isAlive)
	{
		win.draw(m_sprite);
	}
}

sf::Vector2f Particle::Closest(sf::Vector2f pos, sf::Vector2f target)
{
	float dx = pos.x - target.x, dy = pos.y - target.y, x = target.x, y = target.y;
	if (abs(dx) > 1200 && dx != 0)
	{
		x = target.x + 2400 * (dx / abs(dx));
	}
	if (abs(dy) > 900 && dy != 0)
	{
		y = target.y + 1800 * (dy / abs(dy));
	}
	return sf::Vector2f(x, y);
}

void Particle::CheckCollision()
{

}

Particle::~Particle()
{

}