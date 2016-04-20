#ifndef _NPC_CRITTER_
#define _NPC_CRITTER_

#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Emitter.h"
#include <iostream>
using namespace std;

#define DistanceOfNeck 0
#define DistanceOfTail 0

class Critter
{
protected:
	sf::Texture m_bodyTexture;
	sf::Texture m_headTexture;
	sf::Texture m_tailTexture;
	sf::Sprite m_bodySprite;
	sf::Sprite m_headSprite;
	sf::Sprite m_tailSprite;

	sf::Texture m_selectedTex;
	sf::Sprite m_selectedSprite;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	float m_speed;
	float m_rotation;

	float m_attackDamage;
	float m_health;

	int timer = rand() % 300 + 100;
	int dir = rand() % 7 + 1;

	sf::Color m_deathCol = sf::Color(255, 200, 200, 50);
	sf::Color m_colour;
	Emitter m_emitter;
public:
	Critter::Critter() { }
	Critter::~Critter() { }

	bool m_selected = false;
	bool smellDetected = false;

	virtual void Critter::Update()
	{}
	virtual void Critter::Update(sf::Vector2f target)
	{}
	virtual void Critter::Draw(sf::RenderWindow &win)
	{
		m_emitter.Draw(win);
		if (m_selected)
			win.draw(m_selectedSprite);
		if (m_health <= 0)
		{
			m_bodySprite.setColor(m_deathCol);
			m_headSprite.setColor(m_deathCol);
			m_tailSprite.setColor(m_deathCol);
		}
		win.draw(m_bodySprite);
		win.draw(m_headSprite);
		win.draw(m_tailSprite);
	}

	virtual void DecreaseHealth(float val)
	{
		m_health -= val;
		cout << m_health << endl;
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

			m_bodySprite.setPosition(m_position);
			m_bodySprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

			m_selectedSprite.setPosition(m_position);
			m_selectedSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

			m_headSprite.setPosition(m_position + (normalised * (float)DistanceOfNeck));
			m_headSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

			m_tailSprite.setPosition(m_position + (normalised * (float)DistanceOfTail));
			m_tailSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
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
			m_speed = 4.75;
			m_rotation = atan2(diff.y, diff.x);
			m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
			m_position += m_direction * m_speed;
			//m_bodySprite.setRotation(m_rotation * 180 / (22.0f / 7.0f) + 90.0f);
			//Set position of Head and rotation 
			float length = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));
			if (length > 0)
			{
				sf::Vector2f normalised = m_direction / length;
				m_bodySprite.setPosition(m_position);
				m_bodySprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

				m_selectedSprite.setPosition(m_position);
				m_selectedSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

				m_headSprite.setPosition(m_position + (normalised * (float)DistanceOfNeck));
				m_headSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

				m_tailSprite.setPosition(m_position + (normalised * (float)DistanceOfTail));
				m_tailSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
			}
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
			//m_bodySprite.setRotation(m_rotation * 180 / (22.0f / 7.0f) + 90.0f);

			float length = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));
			if (length > 0)
			{
				sf::Vector2f normalised = m_direction / length;
				m_bodySprite.setPosition(m_position);
				m_bodySprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

				m_selectedSprite.setPosition(m_position);
				m_selectedSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

				m_headSprite.setPosition(m_position + (normalised * (float)DistanceOfNeck));
				m_headSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

				m_tailSprite.setPosition(m_position + (normalised * (float)DistanceOfTail));
				m_tailSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
			}
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

	sf::Sprite GetSprite() { return m_bodySprite; }
	sf::Sprite GetHeadSprite() { return m_headSprite; }

	sf::Color GetColour() { return m_colour; }
};

#endif
