#include "NPC_Bear.h"

Bear::Bear() {}

Bear::Bear(float x, float y) 
{
	m_health = 100.0f;

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

	m_tailTexture.loadFromFile("Assets/Graphics/NPC/tailBearNPC.png");
	m_tailTexture.setSmooth(true);

	m_tailSprite.setTexture(m_tailTexture);
	m_tailSprite.setOrigin(10.0f, 2.0f);
	m_tailSprite.setPosition(m_position.x, m_position.y - DistanceOfTail);

	m_selectedTex.loadFromFile("Assets/Graphics/NPC/selectedBear.png");
	m_selectedTex.setSmooth(true);

	m_selectedSprite.setTexture(m_selectedTex);
	m_selectedSprite.setOrigin(m_selectedSprite.getLocalBounds().width / 2, m_selectedSprite.getLocalBounds().height / 2);
	m_selectedSprite.setPosition(m_position.x, m_position.y);

	// Attack animations
	// texture
	m_slashTexture.loadFromFile("Assets/Graphics/Actions/Slash.png");
	m_attackAreaTex.loadFromFile("Assets/Graphics/Actions/attackArea.png");
	m_attackArea.setTexture(m_attackAreaTex);
	// animation
	m_slashAnimation.setSpriteSheet(m_slashTexture);
	m_slashAnimation.addFrame(sf::IntRect(0, 144, 64, 35));
	m_slashAnimation.addFrame(sf::IntRect(0, 108, 64, 35));
	m_slashAnimation.addFrame(sf::IntRect(0, 72, 64, 35));
	m_slashAnimation.addFrame(sf::IntRect(0, 36, 64, 35));
	m_slashAnimation.addFrame(sf::IntRect(0, 0, 64, 35));
	m_slashAnimation.addFrame(sf::IntRect(0, 0, 64, 35));

	m_currentAnimation = &m_slashAnimation;

	m_animatedSprite = AnimatedSprite(sf::seconds(0.065), true, false);
	m_animatedSprite.setOrigin(32, 14);
	m_animatedSprite.setPosition(m_position.x, m_position.y - DistanceOfAttack);

	m_colour = sf::Color::Red;
}

void Bear::Update()
{
	m_bodySprite.setPosition(m_position);
	//Move();
}

void Bear::Update(sf::Vector2f target)
{
	m_bodySprite.setPosition(m_position);
	frameTime = frameClock.restart();

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
		Chase(target);
	}
}

void Bear::Draw(sf::RenderWindow &win)
{
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

	if (m_attacking)
	{
		win.draw(m_animatedSprite);
	}
}

void Bear::Move() // Wander - Needs modifying - find out how m_direction is used in flee and modify for this
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

	else if (dir == 2 && m_position.x < 790) { // Border limits need modifying
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

void Bear::Chase(sf::Vector2f target)	// Chase target
{
	time_t now;

	target = Closest(m_position, target);
	sf::Vector2f diff = m_position - target;
	if (m_attacking)
	{
		m_animatedSprite.update(frameTime);
		m_animatedSprite.move(m_direction * frameTime.asSeconds());

		if (!m_animatedSprite.isPlaying())
		{
			m_attacking = false;
		}
	}

	if (diff.x*diff.x + diff.y*diff.y < 30000 && std::chrono::duration_cast<milliseconds>(Clock::now() - lastHit).count() > 1000)
	{
		m_animatedSprite.play(*m_currentAnimation);
		lastHit = Clock::now();
		m_attacking = true;
		m_speed = 0;
		Player::GetInstance()->DecreaseHealth(20);
	}
	else if (diff.x*diff.x + diff.y*diff.y >= 170000)
	{
		Move();
	}
	else if (diff.x*diff.x + diff.y*diff.y >= 30000 && diff.x*diff.x + diff.y*diff.y < 170000)
	{
		m_speed = 4.5;
		m_rotation = atan2(target.y - m_position.y, target.x - m_position.x);
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

			m_animatedSprite.setPosition(m_position + (normalised * (float)DistanceOfAttack));
			m_animatedSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

			m_attackArea.setPosition(m_position + (normalised * (float)DistanceOfAttack));
			m_attackArea.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
		}
	}
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