#ifndef _PLAYER_
#define _PLAYER_

#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp"
#include "InputManager.h"

#define DistanceOfNeck 35.5

class Player
{
private:
	static bool instanceFlag;
	static Player* instance;

	Player() { }

	sf::Texture m_bodyTexture, m_headTexture;
	sf::Sprite m_bodySprite, m_headSprite;
	float m_roatation;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	float m_speed;
	bool m_running = false;
	bool m_smell = false;

	sf::CircleShape m_smellCircle;
	float m_radius;

	sf::SoundBuffer m_barkBuffer;
	sf::Sound m_barkSound;
public:
	static Player* GetInstance();
	void Init(float, float);

	void Update();
	void Draw(sf::RenderWindow&);

	void Smell();

	~Player()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif