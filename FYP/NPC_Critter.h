#ifndef _NPC_CRITTER_
#define _NPC_CRITTER_

#include "SFML\Graphics.hpp"

#define DistanceOfNeck 0

class Critter
{
protected:
	sf::Texture m_bodyTexture;
	sf::Texture m_headTexture;
	sf::Sprite m_bodySprite;
	sf::Sprite m_headSprite;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	sf::CircleShape m_boundingCircle;

	float m_speed;
	float m_rotation;

	float m_attackDamage;
	float m_health;

	int timer = 200;
	int dir = rand() % 7 + 1;
public:
	Critter::Critter() { }
	Critter::~Critter() { }

	virtual void Critter::Update()
	{

	}
	virtual void Critter::Update(sf::Vector2f target)
	{

	}
	virtual void Critter::Draw(sf::RenderWindow &win)
	{
		win.draw(m_bodySprite);
		win.draw(m_headSprite);
		win.draw(m_boundingCircle);
	}

	// AI Behaviour
	virtual void Move()
	{
		if (timer == 0) {
			timer = 200;
			dir = rand() % 8 + 1; // may want to tweak the probability here
		}

		if (dir == 2 && m_position.x < 790) { // Border limits need modifying
			m_direction.x++;
		}
		else if (dir == 1 && m_position.x > 10) {
			m_direction.x--;
		}
		else if (dir == 4 && m_position.y < 590) {
			m_direction.y++;
		}
		else if (dir == 3 && m_position.y > 10) {
			m_direction.y--;
		}
		else {
			m_direction.x = 0;
			m_direction.y = 0;
		}

		float length = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));

		if (length > 0) {
			sf::Vector2f normalised = m_direction / length;
			m_position += normalised * m_speed;
			m_bodySprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

			m_bodySprite.setPosition(m_position);
			m_headSprite.setPosition(m_position + (normalised * (float)DistanceOfNeck));
			m_headSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
		}
		timer--;
	}
	virtual void Flee(sf::Vector2f target)
	{
		target = Closest(m_position, target);
		sf::Vector2f diff = m_position - target;
		if (diff.x*diff.x + diff.y*diff.y > 200000)
		{
			Move();
			m_speed = 3;
		}
		else
		{
			m_speed = 3;
			m_rotation = atan2(diff.y, diff.x);
			m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
			m_position += m_direction * m_speed;
			m_bodySprite.setRotation(m_rotation * 180 / (22.0f / 7.0f) + 90.0f);
			//Set position of Head and rotation 
		}
	}
	virtual void Chase(sf::Vector2f target)
	{
		target = Closest(m_position, target);
		sf::Vector2f diff = m_position - target;
		if (diff.x*diff.x + diff.y*diff.y < 15000)
			m_speed = 0;
		else if (diff.x*diff.x + diff.y*diff.y >= 15000)
		{
			m_speed = 3;
			m_rotation = atan2(target.y - m_position.y, target.x - m_position.x);
			m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
			m_position += m_direction * m_speed;
			m_bodySprite.setRotation(m_rotation * 180 / (22.0f / 7.0f) + 90.0f);
		}
	}
	virtual void Attack()
	{

	}
	virtual void KeepDistance(sf::Vector2f target)
	{

	}

	//
	sf::Vector2f Closest(sf::Vector2f pos, sf::Vector2f target)
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

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }

	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }

	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }

	sf::CircleShape GetBoundingCircle() { return m_boundingCircle; }
};

#endif