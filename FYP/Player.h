#ifndef _PLAYER_
#define _PLAYER_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "SFML/Audio.hpp"
#include "InputManager.h"
#include "Camera.h"
#include "NPC_Critter.h"

#define DistanceOfNeck 35.5
#define DistanceOfTail 100

class Player
{
private:
	static bool instanceFlag;
	static Player* instance;

	Player() { }

	sf::Texture m_bodyTexture, m_headTexture;
	sf::Sprite m_bodySprite, m_headSprite;

	sf::Texture m_pawTexture;
	sf::Sprite m_paw;

	float m_roatation;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	sf::Vector2f m_headTarget;
	sf::Vector2f m_headPoint;

	float m_speed;
	bool m_running = false;
	bool m_smell = false;

	sf::CircleShape m_pawBounds;
	sf::CircleShape m_playerBounds;

	sf::CircleShape m_smellCircle;
	float m_radius;

	sf::SoundBuffer m_barkBuffer;
	sf::Sound m_barkSound;
	
	int m_health;
	int m_stamina;

	bool m_selected = true;
	sf::Vector2f m_selectedPosition;
public:
	static Player* GetInstance();
	void Init(float, float);

	void Update();
	void Draw(sf::RenderWindow&);

	void Smell(); // Alt Key / Left Bumper
	void Dash(); // Space Bar / Right bumper?
	void Bash();
	void Bite(); // Right Click / Right Trigger
	void Slash(); // Left Click / Left Trigger

	void CheckTargetDistance();

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }
	void SetHealth(float h) { m_health = h; }
	float GetHealth() { return m_health; }
	void SetSelectedNPC(sf::Vector2f target) { m_selectedPosition = target; }
	void SetSelected(bool selected) { m_selected = select; }

	sf::Vector2f GetSelectedNPC() { return m_selectedPosition; }
	bool GetSelected() { return m_selected; }
	
	~Player()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif