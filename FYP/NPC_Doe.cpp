#include "NPC_Doe.h"

Doe::Doe() {}

Doe::Doe(float x, float y)
{
	m_health = 30;

	m_position.x = x;
	m_position.y = y;

	m_bodyTexture.loadFromFile("Assets/Graphics/NPC/bodyDoeNPC.png");
	m_bodyTexture.setSmooth(true);

	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position.x, m_position.y);

	m_headTexture.loadFromFile("Assets/Graphics/NPC/headDoeNPC.png");
	m_headTexture.setSmooth(true);

	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(25.0f, 34.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);

	m_tailTexture.loadFromFile("Assets/Graphics/NPC/tailDoeNPC.png");
	m_tailTexture.setSmooth(true);

	m_tailSprite.setTexture(m_tailTexture);
	m_tailSprite.setOrigin(7.0f, 3.0f);
	m_tailSprite.setPosition(m_position.x, m_position.y - DistanceOfTail);

	m_selectedTex.loadFromFile("Assets/Graphics/NPC/selectedDoe.png");
	m_selectedTex.setSmooth(true);

	m_selectedSprite.setTexture(m_selectedTex);
	m_selectedSprite.setOrigin(m_selectedSprite.getLocalBounds().width / 2, m_selectedSprite.getLocalBounds().height / 2);
	m_selectedSprite.setPosition(m_position.x, m_position.y);

	m_colour = sf::Color::Yellow;
	m_emitter = Emitter(m_position.x, m_position.y, m_colour);

	//Sounds
	m_injuredBuffer.loadFromFile("Assets/Audio/NPC/Doe/doeSound.wav");
	m_injuredSound.setBuffer(m_injuredBuffer);
	m_injuredSound.setRelativeToListener(false);
	//m_injuredSound.setPosition(200, 200, 0);
	m_injuredSound.setAttenuation(5);

	m_deathBuffer.loadFromFile("Assets/Audio/NPC/Doe/doeDead.wav");
	m_deathSound.setBuffer(m_deathBuffer);
	m_deathSound.setRelativeToListener(false);
	m_deathSound.setAttenuation(10);
}

void Doe::Update(sf::Vector2f target)
{
	m_injuredSound.setPosition(m_position.x, m_position.y, 0);
	m_deathSound.setPosition(m_position.x, m_position.y, 0);
	if (!m_dead)
	{
		if (smellDetected)
		{
			m_emitter.SetAlive(true);
			m_emitter.SetPosition(m_position);
		}
		m_emitter.Update(target);

		if (Player::GetInstance()->m_selected == false)
		{
			m_selected = false;
		}
		if (m_health <= 0)
		{ 
			m_selected = false;
			m_dead = true;
		}
		else
		{
			Flee(target);
		}
		if (m_health == 0)
		{
			m_deathSound.setMinDistance(500);
			m_deathSound.setPosition(m_position.x, m_position.y, 0);
			m_deathSound.play();
			Player::GetInstance()->IncreaseHealth(15);
			Player::GetInstance()->SetMaxHealth(Player::GetInstance()->GetMaxHealth() + 2);
			Player::GetInstance()->SetMaxStamina(Player::GetInstance()->GetMaxStamina() + 2);
		}
	}
}

void Doe::Flee(sf::Vector2f target)
{
	target = Closest(m_position, target);
	sf::Vector2f diff = m_position - target;
	if (diff.x*diff.x + diff.y*diff.y > 100000)
	{
		m_speed = 3;
		Move();
	}
	else
	{
		m_speed = 8.25f;
		m_rotation = atan2(diff.y, diff.x);
		m_direction = sf::Vector2f(cos(m_rotation), sin(m_rotation));
		m_position += m_direction * m_speed;
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

void Doe::Move()
{
	if (timer == 0) {
		timer = rand() % 300 + 100;
		dir = rand() % 8 + 1; // may want to tweak the probability here
	}

	if (m_position.x < 30)
	{
		m_direction.x++;
	}
	if (m_position.x > 5300)
	{
		m_direction.x--;
	}
	if (m_position.y < 30)
	{
		m_direction.y++;
	}
	if (m_position.y > 5300)
	{
		m_direction.y--;
	}

	else if (dir == 2 && m_position.x < 5300) { // Border limits need modifying
		m_direction.x++;
	}
	else if (dir == 1 && m_position.x > 30) {
		m_direction.x--;
	}
	else if (dir == 4 && m_position.y < 5300) {
		m_direction.y++;
	}
	else if (dir == 3 && m_position.y > 30) {
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