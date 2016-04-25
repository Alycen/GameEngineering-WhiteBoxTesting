#include "Player.h"
#include <iostream>

using namespace std;

bool Player::instanceFlag = false;
Player* Player::instance = NULL;

Player* Player::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Player();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void Player::Init()
{
	// Player Body Sprite
	// Body Texture
	m_bodyTexture.loadFromFile("Assets/Graphics/Player/body1.png");
	m_bodyTexture.setSmooth(true);

	// Body Sprite
	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position);
	// m_bodySprite.setScale(xScale,yScale);

	// Player Head Sprite
	// Head Texture
	m_headTexture.loadFromFile("Assets/Graphics/Player/head1.png");
	m_headTexture.setSmooth(true);

	// Head Sprite
	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(20.0f, 40.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);
	// m_headSprite.setScale(xScale, yScale);
	
	// Player Tail Sprite
	// Tail Texture
	m_tailTexture.loadFromFile("Assets/Graphics/Player/tail1.png");
	m_tailTexture.setSmooth(true);

	// Tail Sprite
	m_tailSprite.setTexture(m_tailTexture);
	m_tailSprite.setOrigin(12.0f, 4.0f);
	m_tailSprite.setPosition(m_position.x, m_position.y - DistanceOfTail);

	m_smellTex.loadFromFile("Assets/Graphics/Actions/Smell.png");
	m_smellTex.setSmooth(true);

	m_smellSprite.setTexture(m_smellTex);
	m_smellSprite.setOrigin(m_smellSprite.getGlobalBounds().width / 2, m_smellSprite.getLocalBounds().height / 2);
	m_smellSprite.setPosition(m_position);

	// Mouse / Paw
	m_pawTexture.loadFromFile("Assets/Graphics/Player/Paw.png");
	m_pawTexture.setSmooth(true);
	m_paw.setTexture(m_pawTexture);
	m_paw.setOrigin(m_paw.getLocalBounds().width / 2, m_paw.getLocalBounds().height / 2);

	// Player Temp Bark Sound
	//m_barkBuffer.loadFromFile("Assets/Audio/Player/.wav");
	//m_barkSound.setBuffer(m_barkBuffer);

	

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

	sf::Listener::setDirection(0, 1, 0);
	sf::Listener::setUpVector(0, 0, 1);

	m_hitBuffer.loadFromFile("Assets/Audio/NPC/hit.wav");
	m_hitSound.setBuffer(m_hitBuffer);
	m_hitSound.setRelativeToListener(true);
	m_hitSound.setVolume(70);

	m_deathBuffer.loadFromFile("Assets/Audio/NPC/playerDead.wav");
	m_deathSound.setBuffer(m_deathBuffer);
	m_deathSound.setRelativeToListener(true);

}

// Load stats from txt file()
// Write stats to txt file()
/*
{
	save map;
	m_health;`
	m_stamina;
	m_attack;
	m_position;
}*/

void Player::Update()
{
	sf::Listener::setPosition(m_position.x, m_position.y, 0);

	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
	if (m_stamina > m_maxStamina)
		m_stamina = m_maxStamina;

	if (m_position.x < 100)
	{
		m_position.x = 100;
	}
	if (m_position.x > 5300)
	{
		m_position.x = 5300;
	}
	if (m_position.y < 100)
	{
		m_position.y = 100;
	}
	if (m_position.y > 5300)
	{
		m_position.y = 5300;
	}

	m_smellSprite.setPosition(m_position);
	m_paw.setPosition(InputManager::GetInstance()->GetMousePosWorld());
	sf::Time frameTime = frameClock.restart();
	bool moving;

	//X-Axis
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::A)) 
	{
		m_direction.x--;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::A))
	{
		m_direction.x++;
	}
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::D)) 
	{
		m_direction.x++;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::D))
	{
		m_direction.x--;
	}

	//Y-Axis
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::W)) 
	{
		m_direction.y--;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::W))
	{
		m_direction.y++;
	}
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::S)) 
	{
		m_direction.y++;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::S))
	{
		m_direction.y--;
	}

	if (InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::W) || InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::A) || InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::S) || InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::D))
	{
		moving = true;
	}
	else
	{
		moving = false;
	}

	// Run
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::LShift)) 
	{
		m_running = true;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::LShift)) 
	{
		m_running = false;
	}

	// Modify Speed if Player is running or not
	if (m_running && m_stamina > 1 && moving) 
	{
		m_speed = 10.0f;
		m_stamina -= 0.25f;
	}
	else
	{
		m_speed = 4.5f;
		if (m_stamina < m_maxStamina )
		{
			m_stamina += 0.125f;
		}
	}

	// Smell
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyDown(sf::Keyboard::RAlt)) 
	{
		Smell();
	}
	if ((InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::RAlt)) &&  smellScale <= 1) 
	{
		m_smell = true;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::RAlt) || smellScale <= 1)
	{
		m_smell = false;
	}

	// Attack Inputs
	// Slash
	if ((InputManager::GetInstance()->IsKeyDown(sf::Keyboard::E) || InputManager::GetInstance()->IsMouseButtonDown(1)) && !m_attacking)
	{
		m_attacking = true;
		m_animatedSprite.play(*m_currentAnimation);
		m_animatedSprite.move(m_direction * frameTime.asSeconds());
	}
	m_animatedSprite.update(frameTime);
	if (!m_animatedSprite.isPlaying())
	{
		m_attacking = false;
	}

	//Normalise direction
	float length = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));

	if (length > 0) 
	{
		sf::Vector2f normalised = m_direction / length;
		m_position += normalised * m_speed;

		m_bodySprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

		m_bodySprite.setPosition(m_position);

		m_headSprite.setPosition(m_position + (normalised * (float)DistanceOfNeck));
		m_headSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

		m_tailSprite.setPosition(m_position + (normalised * (float)DistanceOfTail));
		m_tailSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

		m_animatedSprite.setPosition(m_position + (normalised * (float)DistanceOfAttack));
		m_animatedSprite.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);

		m_attackArea.setPosition(m_position + (normalised * (float)DistanceOfAttack));
		m_attackArea.setRotation(atan2(normalised.y, normalised.x) * 180 / (22.0f / 7.0f) + 90.0f);
	}

	if (m_selected)
	{
		sf::Vector2f targ;
		targ.x = (m_position.x + m_selectedPosition.x) / 2;
		targ.y = (m_position.y + m_selectedPosition.y) / 2;

		Camera::GetInstance()->setViewPosition(targ);

		sf::Vector2f target = Closest(m_position, targ);
		sf::Vector2f diff = m_position - target;
		if (diff.x*diff.x + diff.y*diff.y > 180000)
		{
			m_selected = false;
		}
		else
		{
			m_selected = true;
		}
		if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::Escape))
		{
			m_selected = false;
		}
	}
	else if (!m_selected)
	{
		Camera::GetInstance()->setViewPosition(m_position);
	}
	if (m_health <= 0)
	{
		m_deathSound.play();
		Reset();
	}

	if (m_health < m_maxHealth) // Players health slowly regens
	{
		m_health += 0.025f;
	}
}

void Player::Smell() 
{
	// Reset all smell variables
	smellScale = 0.001f;
}

void Player::Draw(sf::RenderWindow &win)
{
	win.draw(m_bodySprite);
	win.draw(m_headSprite);
	win.draw(m_tailSprite);

	if (m_attacking)
		win.draw(m_animatedSprite);

	if (m_smell)  
	{
		win.draw(m_smellSprite);
		if (smellScale <= 1)
		{
			smellScale += 0.005f;
			m_smellSprite.setScale(smellScale, smellScale);
		}
		else if (smellScale >= 1) 
		{
			m_smell = false;
		}
	}
	win.draw(m_paw);
}

sf::Vector2f Player::Closest(sf::Vector2f pos, sf::Vector2f target)
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

void Player::Save()
{
	ofstream savefile("SaveFiles/save1.txt");

	if (savefile.is_open())
	{
		savefile << m_health << endl;
		savefile << m_maxHealth << endl;
		savefile << m_stamina << endl;
		savefile << m_maxStamina << endl;
		savefile << m_position.x << endl;
		savefile << m_position.y << endl;
		savefile << m_attackDamage << endl;
		
		savefile.close();
	}
	else cout << "Can't write to save file";
}

void Player::Load()
{
	string line;
	ifstream savefile("SaveFiles/save1.txt");
	vector<string> data;

	if (savefile.is_open())
	{
		while (!savefile.eof())
		{
			getline(savefile, line);
			data.push_back(line);
		}
		savefile.close();
		if (data.size() == 1)
		{
			Reset();
		}
		else
		{
			m_health = stof(data.at(0));
			m_maxHealth = stof(data.at(1));
			m_stamina = stof(data.at(2));
			m_maxStamina = stof(data.at(3));
			m_position.x = stof(data.at(4));
			m_position.y = stof(data.at(5));
			m_attackDamage = stof(data.at(6));	
		}
	}
	else cout << "Can't open save file";
}

void Player::Reset() // If you die or start a new game, your stats reset
{
	m_position.x = 3000;
	m_position.y = 2500;

	// Stats
	m_maxHealth = 100;
	m_health = m_maxHealth;

	m_maxStamina = 120;
	m_stamina = m_maxStamina;

	// Attack Damage 
	m_attackDamage = 1.0f;
}