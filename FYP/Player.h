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

	//sf::CircleShape m_pawBounds;
	//sf::CircleShape m_playerBounds;

	sf::CircleShape m_smellCircle;
	float m_radius;

	sf::SoundBuffer m_barkBuffer;
	sf::Sound m_barkSound;
	
	float m_maxHealth, m_health;
	float m_maxStamina, m_stamina;

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

	bool m_selected = false;

	sf::Vector2f Closest(sf::Vector2f, sf::Vector2f);

	void CheckTargetDistance();

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }
	// Health
	void SetHealth(float h) { m_health = h; }
	float GetHealth() { return m_health; }
	void SetMaxHealth(float h) { m_maxHealth = h; }
	float GetMaxHealth() { return m_maxHealth; }
	// Stamina
	void SetStamina(float s) { m_stamina = s; }
	float GetStamina() { return m_stamina; }
	void SetMaxStamina(float s) { m_maxStamina = s; }
	float GetMaxStamina() { return m_maxStamina; }

	//NPC target
	void SetSelectedNPC(sf::Vector2f target) { m_selectedPosition = target; }
	void SetSelected(bool selected) { m_selected = select; }
	sf::Vector2f GetSelectedNPC() { return m_selectedPosition; }
	bool GetSelected() { return m_selected; }

	//sf::CircleShape GetBoundingCircle() { return m_playerBounds; }
	//sf::CircleShape GetBoundingPaw() { return m_pawBounds; }

	sf::Sprite GetSprite() { return m_bodySprite; }
	sf::Sprite GetPawSprite() { return m_paw; }
	
	~Player()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif