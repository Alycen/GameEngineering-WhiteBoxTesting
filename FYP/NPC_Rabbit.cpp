#include "NPC_Rabbit.h"

Rabbit::Rabbit() {}

Rabbit::Rabbit(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyRabbitNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);

	m_headTexture.loadFromFile("Assets/Graphics/NPC/headRabbitNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(11.0f, 18.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);
}

void Rabbit::Update(sf::Vector2f target)
{
	m_bodySprite.setPosition(m_position);
	Flee(target);
}

void Rabbit::Flee(sf::Vector2f target)
{
	target = Closest(m_position, target);
	sf::Vector2f diff = m_position - target;
	if (diff.x*diff.x + diff.y*diff.y > 200000)
	{
		m_speed = 3;
		Move();
	//	m_speed = 0;
	}
	else
	{
		m_speed = 8;
		m_rotation = atan2(diff.y, diff.x);
		m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
		m_position += m_direction * m_speed;
		m_bodySprite.setRotation(m_rotation * 180 / (22.0f / 7.0f) + 90.0f);
		//Set position of Head and rotation 
	}
}

void Rabbit::Move()
{
	if (timer == 0) {
		timer = 200;
		dir = rand() % 10 + 1; // may want to tweak the probability here
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