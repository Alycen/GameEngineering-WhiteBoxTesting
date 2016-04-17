#ifndef _GAMESCENE_
#define _GAMESCENE_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

#include "Player.h"
#include "NPC_Kanine.h"
#include "NPC_Bear.h"
#include "NPC_Stag.h"
#include "NPC_Doe.h"
#include "NPC_Rabbit.h"
#include "Camera.h"
#include <list>
#include "STP\TMXLoader.hpp"
#include "UI_bar.h"
#include "Collision.h"

class GameScene
{
private:
	static bool instanceFlag;
	static GameScene* instance;
	GameScene() { }

	sf::Music m_backgroundMusic;

	list<Critter*> npcs;

	int wolfNum, bearNum, stagNum, doeNum, rabbitNum;

	UI_bar* m_healthbar;
	UI_bar* m_staminabar;

	tmx::TileMap* m_map;
public:
	static GameScene* GetInstance();

	void Init();
	void Update();
	void Draw(sf::RenderWindow&);

	// UI Bars
	void UpdateHealth();
	void UpdateStamina();

	// Checks
	void CheckMouseCollision();
	void CheckPlayerCollision();
	void CheckNPCsCollisions();

	void CheckLevelChange();
	void CheckPlayerSmell();

	GameScene::~GameScene()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif