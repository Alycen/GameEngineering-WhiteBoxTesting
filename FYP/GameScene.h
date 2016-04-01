#ifndef _GAMESCENE_
#define _GAMESCENE_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

#include "Player.h"
#include "NPC_Kanine.h"
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

	tmx::TileMap* m_map;

	UI_bar* temp_healtbar;
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