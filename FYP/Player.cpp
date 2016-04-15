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

void Player::Init(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	// Player Body Sprite
	// Body Texture
	m_bodyTexture.loadFromFile("Assets/Graphics/Player/body.png");
	m_bodyTexture.setSmooth(true);

	// Body Sprite
	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setOrigin(m_bodySprite.getLocalBounds().width / 2, m_bodySprite.getLocalBounds().height / 2);
	m_bodySprite.setRotation(0);
	m_bodySprite.setPosition(m_position);
	// m_bodySprite.setScale(xScale,yScale);

	// Player Head Sprite
	// Head Texture
	m_headTexture.loadFromFile("Assets/Graphics/Player/head.png");
	m_headTexture.setSmooth(true);

	// Head Sprite
	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setOrigin(20.0f, 40.0f);
	m_headSprite.setPosition(m_position.x, m_position.y - DistanceOfNeck);
	// m_headSprite.setScale(xScale, yScale);

	// Bounding Circle
	m_playerBounds.setOrigin(m_bodySprite.getOrigin().x + (m_bodySprite.getLocalBounds().width / 5.5), m_bodySprite.getOrigin().y);
	m_playerBounds.setRadius(m_bodySprite.getLocalBounds().height / 2);
	m_playerBounds.setFillColor(sf::Color::Transparent);
	m_playerBounds.setOutlineColor(sf::Color::Red);
	m_playerBounds.setOutlineThickness(3);
	
	// Mouse / Paw
	m_pawTexture.loadFromFile("Assets/Graphics/Player/Paw.png");
	m_pawTexture.setSmooth(true);
	m_paw.setTexture(m_pawTexture);
	m_paw.setOrigin(m_paw.getLocalBounds().width / 2, m_paw.getLocalBounds().height / 2);
	m_pawBounds.setOrigin(21.5f, 21.5f);
	m_pawBounds.setRadius(21.5f);
	m_pawBounds.setFillColor(sf::Color::Transparent);
	m_pawBounds.setOutlineColor(sf::Color::Black);
	m_pawBounds.setOutlineThickness(3);

	// Player Temp Bark Sound
	//m_barkBuffer.loadFromFile("Assets/Audio/Player/.wav");
	//m_barkSound.setBuffer(m_barkBuffer);

	// Smell Area Radius
	m_radius = 950.0f;

	// Stats
	m_health = 100;
	// Attack Damage 
}

// Load stats from txt file()
// Write stats to txt file()

void Player::Update()
{
	m_paw.setPosition(InputManager::GetInstance()->GetMousePosWorld());

	m_pawBounds.setPosition(m_paw.getPosition());
	m_playerBounds.setPosition(m_position);

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
	if (m_running) 
	{
		m_speed = 10.0f;
	}
	else if ((InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::Space)))
	{
		m_speed = 22.0f;
	}
	else
	{
		m_speed = 4.5f;
	}

	// Smell
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyDown(sf::Keyboard::RAlt)) 
	{
		Smell();
		//m_selected = true;     // for debugging purposes
	}
	if ((InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::RAlt)) && m_smellCircle.getRadius() < m_radius) 
	{
		m_smell = true;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::RAlt) || m_smellCircle.getRadius() >= m_radius) 
	{
		m_smell = false;
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
	}
	float dx = InputManager::GetInstance()->GetMousePosWorld().x - (m_headSprite.getGlobalBounds().width / 2); // Wrong points for head
	float dy = InputManager::GetInstance()->GetMousePosWorld().y - (m_headSprite.getGlobalBounds().height - m_headTexture.getSize().y);

	//cout << "Mouse X : " << (m_headSprite.getLocalBounds().width / 2) << ", Mouse Y : " << (m_headSprite.getLocalBounds().height - m_headTexture.getSize().y) << endl;
	m_headSprite.setRotation(atan2(dy, dx) * 180 / (22.0f / 7.0f));

	if (m_selected)
	{
		sf::Vector2f targ;
		targ.x = (m_position.x + m_selectedPosition.x) / 2;
		targ.y = (m_position.y + m_selectedPosition.y) / 2;

		Camera::GetInstance()->setViewPosition(targ);
		sf::Vector2f target = Closest(m_position, targ);
		sf::Vector2f diff = m_position - target;
		if (diff.x*diff.x + diff.y*diff.y > 150000)
		{
			m_selected = false;
		}
		else
		{
			m_selected = true;
		}
	}
	else if (!m_selected)
	{
		Camera::GetInstance()->setViewPosition(m_position);
	}
}

void Player::Smell() 
{
	//smellCircle.setOrigin(position);
	m_smellCircle.setPosition(m_position.x - (m_smellCircle.getRadius()), m_position.y - (m_smellCircle.getRadius()));
	m_smellCircle.setRadius(0.0f);
	m_smellCircle.setFillColor(sf::Color::Transparent);
	m_smellCircle.setOutlineColor(sf::Color::White);
	m_smellCircle.setOutlineThickness(3);
}

void Player::Dash()
{
	// No Damage
}

void Player::Bash()
{
	// Damage = 5; (Have it be a multiplier)
}

void Player::Bite()
{
	// Damage = 15
}

void Player::Slash()
{
	// Damage = 20
}

void Player::Draw(sf::RenderWindow &win)
{
	win.draw(m_bodySprite);
	win.draw(m_headSprite);
	
	if (m_smell)  
	{
		win.draw(m_smellCircle);
		if (m_smellCircle.getRadius() < m_radius) 
		{
			m_smellCircle.setRadius(m_smellCircle.getRadius() + 4.5f);
			m_smellCircle.setPosition(m_position.x - (m_smellCircle.getRadius()), m_position.y - (m_smellCircle.getRadius()));
		}
		else if (m_smellCircle.getRadius() >= m_radius) 
		{
			m_smell = false;
		}
	}
	win.draw(m_paw);
	win.draw(m_pawBounds);
	win.draw(m_playerBounds);
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