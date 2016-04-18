#ifndef _PLAYER_
#define _PLAYER_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "SFML/Audio.hpp"
#include "InputManager.h"
#include "Camera.h"
#include "NPC_Critter.h"
#include "AnimateSprite.h"

#define DistanceOfNeck 35.5
#define DistanceOfTail -35
#define DistanceOfAttack 105

class Player
{
private:
	static bool instanceFlag;
	static Player* instance;

	Player() { }
	// Sprite variables
	sf::Texture m_bodyTexture, m_headTexture, m_tailTexture;
	sf::Sprite m_bodySprite, m_headSprite, m_tailSprite;

	sf::Texture m_pawTexture;
	sf::Sprite m_paw;

	// Position & position manipulators
	float m_roatation;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	// Player bools
	bool m_running = false;
	bool m_smell = false;
	bool m_attacking = false;

	//sf::CircleShape m_smellCircle;
	//float m_radius;
	// Player Sounds
	sf::SoundBuffer m_barkBuffer;
	sf::Sound m_barkSound;
	// Stats
	float m_maxHealth, m_health;
	float m_maxStamina, m_stamina;
	float m_speed;
	// Target variables
	sf::Vector2f m_selectedPosition;

	// Animations / Attacks / Actions
	sf::Texture m_smellTex;
	sf::Sprite m_smellSprite;
	float smellScale = 0.001f;

	sf::Texture m_slashTexture, m_attackAreaTex;
	sf::Sprite m_attackArea;
	Animation m_slashAnimation;
	Animation* m_currentAnimation;
	// Animated Sprite
	AnimatedSprite m_animatedSprite;

	// Clock
	sf::Clock frameClock;
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
	bool isAttacking() { return m_attacking; }

	sf::Vector2f Closest(sf::Vector2f, sf::Vector2f);

	// Get / Sets
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }

	sf::Sprite GetSmellSprite() { return m_smellSprite; }
	//sf::Sprite GetAttackingSprite() { return  }

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

	sf::Sprite GetSprite() { return m_bodySprite; }
	sf::Sprite GetHeadSprite() { return m_headSprite; }
	sf::Sprite GetPawSprite() { return m_paw; }
	sf::Sprite GetAttackArea() { return m_attackArea; }
	
	~Player()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif