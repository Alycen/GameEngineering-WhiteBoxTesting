#include "NPC_Bear.h"

// look into exactly waht Flee() and other 
// methods bar move, do with m_direction

Bear::Bear() {}

Bear::Bear(float x, float y) 
{
	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyBearNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);

	m_headTexture.loadFromFile("Assets/Graphics/NPC/headBearNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(27.0f, 56.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);
}

void Bear::Update()
{
	m_bodySprite.setPosition(m_position);
	//Move();
}

void Bear::Update(sf::Vector2f target)
{
	m_bodySprite.setPosition(m_position);
	//Move();
	//Flee(target);
	Chase(target);
}

void Bear::Draw(sf::RenderWindow &win)
{
	win.draw(m_bodySprite);
	//win.draw(m_headSprite);
}

void Bear::Move() // Wander - Needs modifying - find out how m_direction is used in flee and modify for this
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

void Bear::Flee(sf::Vector2f target)	// Run from target
{
	target = Closest(m_position, target);
	sf::Vector2f diff = m_position - target;
	if (diff.x*diff.x + diff.y*diff.y > 200000)
		m_speed = 0;
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

void Bear::Chase(sf::Vector2f target)	// Chase target
{
	target = Closest(m_position, target);
	sf::Vector2f diff = m_position - target;
	if (diff.x*diff.x + diff.y*diff.y < 15000)
	{
		m_speed = 0;
	}
	else if (diff.x*diff.x + diff.y*diff.y >= 150000)
	{
		Move();
	}
	else if (diff.x*diff.x + diff.y*diff.y >= 15000 && diff.x*diff.x + diff.y*diff.y < 150000)
	{
		m_speed = 3;
		m_rotation = atan2(target.y - m_position.y, target.x - m_position.x);
		m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
		m_position += m_direction * m_speed;
		m_bodySprite.setRotation(m_rotation * 180 / (22.0f / 7.0f) + 90.0f);
	}
}

void Bear::Attack()	//
{

}

void Bear::KeepDistance(sf::Vector2f target)
{
	target = Closest(m_position, target);
	m_speed = (sqrt(pow(m_position.x - target.x, 2) + pow(m_position.y - target.y, 2)) - 80) / 120.0f;
	if (m_speed < 5 / 120.0f)
		m_speed = 0;
	else
	{
		m_speed /= 0.45f;
		if (m_speed > 1.3f)
		{
			m_speed = 1.3f;
		}
	}
	m_rotation = atan2(target.y - m_position.y, target.x - m_position.x);
	m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
}


sf::Vector2f Bear::Closest(sf::Vector2f pos, sf::Vector2f target)
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