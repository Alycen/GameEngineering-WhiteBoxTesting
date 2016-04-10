#ifndef _GAMESCENE_
#define _GAMESCENE_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

#include "Player.h"
#include "NPC_Kanine.h"
#include "NPC_Bear.h"
#include "NPC_Stag.h"
#include "NPC_Doe.h"
#include "Camera.h"
#include <list>
#include "STP\TMXLoader.hpp"
#include "UI_bar.h"

class GameScene
{
private:
	static bool instanceFlag;
	static GameScene* instance;
	GameScene() { }

	sf::Music m_backgroundMusic;
	Kanine* testKanine;
	Bear* testBear;
	Stag* testStag;
	Doe* bambisMom;

	UI_bar* temp_healtbar;
	UI_bar* temp_staminabar;

	tmx::TileMap* m_map;
public:
	static GameScene* GetInstance();
	~GameScene()
	{
		delete instance;
		instanceFlag = false;
	}
	void Init();
	void Update();
	void Draw(sf::RenderWindow&);
};

#endif