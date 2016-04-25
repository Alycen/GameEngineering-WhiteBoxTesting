#include "NPC_Stag.h"

Stag::Stag() {}

Stag::Stag(float x, float y)
{
	m_health = 70;

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

	m_tailTexture.loadFromFile("Assets/Graphics/NPC/tailStagNPC.png");
	m_tailTexture.setSmooth(true);

	m_tailSprite.setTexture(m_tailTexture);
	m_tailSprite.setOrigin(9.0f, 3.0f);
	m_tailSprite.setPosition(m_position.x, m_position.y - DistanceOfTail);

	m_selectedTex.loadFromFile("Assets/Graphics/NPC/selectedStag.png");
	m_selectedTex.setSmooth(true);

	m_selectedSprite.setTexture(m_selectedTex);
	m_selectedSprite.setOrigin(m_selectedSprite.getLocalBounds().width / 2, m_selectedSprite.getLocalBounds().height / 2);
	m_selectedSprite.setPosition(m_position.x, m_position.y);

	// Attack animations
	// texture
	m_bashTexture.loadFromFile("Assets/Graphics/Actions/bashSheet.png");
	m_attackAreaTex.loadFromFile("Assets/Graphics/Actions/attackArea.png");
	m_attackArea.setTexture(m_attackAreaTex);
	// animation
	m_bashAnimation.setSpriteSheet(m_bashTexture);
	m_bashAnimation.addFrame(sf::IntRect(0, 144, 64, 35));
	m_bashAnimation.addFrame(sf::IntRect(0, 108, 64, 35));
	m_bashAnimation.addFrame(sf::IntRect(0, 72, 64, 35));
	m_bashAnimation.addFrame(sf::IntRect(0, 36, 64, 35));
	m_bashAnimation.addFrame(sf::IntRect(0, 0, 64, 35));

	m_currentAnimation = &m_bashAnimation;

	m_animatedSprite = AnimatedSprite(sf::seconds(0.085), true, false);
	m_animatedSprite.setOrigin(32, 14);
	m_animatedSprite.setPosition(m_position.x, m_position.y - DistanceOfAttack);

	m_speed = 2.5;

	m_colour = sf::Color(255,162,68,100);
	m_emitter = Emitter(m_position.x, m_position.y, m_colour);

	//Sounds
	//m_injuredBuffer.loadFromFile("Assets/Audio/NPC/Doe/doeSound.wav");
	//m_injuredSound.setBuffer(m_injuredBuffer);
	//m_injuredSound.setRelativeToListener(false);
	//m_injuredSound.setPosition(200, 200, 0);
	//m_injuredSound.setAttenuation(5);

	m_deathBuffer.loadFromFile("Assets/Audio/NPC/Stag/stagDead.wav");
	m_deathSound.setBuffer(m_deathBuffer);
	m_deathSound.setRelativeToListener(false);
	m_deathSound.setAttenuation(10);
}

void Stag::Update(sf::Vector2f target)
{
	frameTime = frameClock.restart();

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
		else if (m_health < 70 && m_health >= 20) // If the player attacked the Stag
		{
			Chase(target);
		}
		else if (m_health < 20 && m_health > 0)
		{
			Flee(target);
		}
		else 
		{
			Move();
		}

		if (m_health == 0)
		{
			m_deathSound.setMinDistance(500);
			m_deathSound.setPosition(m_position.x, m_position.y, 0);
			m_deathSound.play();

			Player::GetInstance()->IncreaseHealth(20);
			Player::GetInstance()->SetMaxHealth(Player::GetInstance()->GetMaxHealth() + 3);
			Player::GetInstance()->SetMaxStamina(Player::GetInstance()->GetMaxStamina() + 3);
		}
	}
}

void Stag::Move()
{
	m_attacking = false;
	if (timer == 0) {
		timer = rand() % 300 + 100;
		dir = rand() % 7 + 1; // may want to tweak the probability here
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

	else if (dir == 2 && m_position.x < 53000) { // Border limits need modifying
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

		m_animatedSprite.setPosition(m_position + (normalised * (float)DistanceOfAttack));
		m_animatedSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

		m_attackArea.setPosition(m_position + (normalised * (float)DistanceOfAttack));
		m_attackArea.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
	}
	timer--;
}

void Stag::Chase(sf::Vector2f target)
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

	if (Collision::CircleTest(m_headSprite, Player::GetInstance()->GetSprite()) && std::chrono::duration_cast<milliseconds>(Clock::now() - lastHit).count() > 1000)
	{
		m_animatedSprite.play(*m_currentAnimation);
		lastHit = Clock::now();
		m_attacking = true;
		m_speed = 0;
		Player::GetInstance()->DecreaseHealth(10);
	}
	else if (diff.x*diff.x + diff.y*diff.y >= 18000)
	{
		m_speed = 5;
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

void Stag::Flee(sf::Vector2f target)
{
	m_attacking = false;
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


void Stag::Draw(sf::RenderWindow &win)
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

	if (m_attacking)
	{
		win.draw(m_animatedSprite);
	}
}