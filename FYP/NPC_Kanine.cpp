#include "NPC_Kanine.h"

Kanine::Kanine() {}

Kanine::Kanine(float x, float y)
{
	m_health = 60;

	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyKanineNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);
	
	m_headTexture.loadFromFile("Assets/Graphics/NPC/headKanineNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(20.0f, 40.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);

	m_tailTexture.loadFromFile("Assets/Graphics/NPC/tailKanineNPC.png");
	m_tailTexture.setSmooth(true);

	m_tailSprite.setTexture(m_tailTexture);
	m_tailSprite.setOrigin(12.0f, 4.0f);
	m_tailSprite.setPosition(m_position.x, m_position.y - DistanceOfTail);
}

void Kanine::Update()
{
	m_bodySprite.setPosition(m_position.x, m_position.y);
	Move();
}

void Kanine::Draw(sf::RenderWindow &win)
{
	win.draw(m_bodySprite);
	win.draw(m_headSprite);
	win.draw(m_tailSprite);
}

void Kanine::Move()
{
	if (timer == 0) {
		timer = rand() % 300 + 100;
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

		m_tailSprite.setPosition(m_position + (normalised * (float)DistanceOfTail));
		m_tailSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
	}
	timer--;
}