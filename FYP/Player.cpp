#include "Player.h"

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
	

	// Player Temp Bark Sound
	//m_barkBuffer.loadFromFile("Assets/Audio/Player/.wav");
	//m_barkSound.setBuffer(m_barkBuffer);

	// Smell Area Radius
	m_radius = 500.0f;
}

void Player::Update()
{
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
	if (m_running) {
		m_speed = 0.25f;
	}
	else {
		m_speed = 0.115f;
	}

	// Smell
	if (InputManager::GetInstance()->IsKeyDown(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyDown(sf::Keyboard::RAlt)) {
		Smell();
	}
	if ((InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyHeld(sf::Keyboard::RAlt)) && m_smellCircle.getRadius() < m_radius) {
		m_smell = true;
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::LAlt) || InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::RAlt) || m_smellCircle.getRadius() >= m_radius) {
		m_smell = false;
	}

	// if (m_smell) {}

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

void Player::Draw(sf::RenderWindow &win)
{
	win.draw(m_bodySprite);
	win.draw(m_headSprite);
	
	if (m_smell)  
	{
		win.draw(m_smellCircle);
		if (m_smellCircle.getRadius() < m_radius) 
		{
			m_smellCircle.setRadius(m_smellCircle.getRadius() + .15f);
			m_smellCircle.setPosition(m_position.x - (m_smellCircle.getRadius()), m_position.y - (m_smellCircle.getRadius()));
		}
		else if (m_smellCircle.getRadius() >= m_radius) 
		{
			m_smell = false;
		}
	}
}