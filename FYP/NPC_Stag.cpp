#include "NPC_Stag.h"

Stag::Stag() {}

Stag::Stag(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyStagNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);

	m_headTexture.loadFromFile("Assets/Graphics/NPC/headStagNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(60.0f, 45.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);

	// Bounding Circle
	m_boundingCircle.setRadius(m_bodySprite.getLocalBounds().height / 2);
	m_boundingCircle.setOrigin(m_bodySprite.getOrigin().x + (m_bodySprite.getLocalBounds().width / 2.5), m_bodySprite.getOrigin().y);
	m_boundingCircle.setFillColor(sf::Color::Transparent);
	m_boundingCircle.setOutlineColor(sf::Color::Yellow);
	m_boundingCircle.setOutlineThickness(3);

	m_speed = 2.5;
}

void Stag::Update(sf::Vector2f target)
{
	m_bodySprite.setPosition(m_position);
	m_boundingCircle.setPosition(m_position);
	Move();
}

void Stag::Move()
{
	if (timer == 0) {
		timer = 200;
		dir = rand() % 7 + 1; // may want to tweak the probability here
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