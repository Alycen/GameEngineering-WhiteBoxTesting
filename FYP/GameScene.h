#ifndef _GAMESCENE_
#define _GAMESCENE_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

#include "Player.h"
#include <list>

class GameScene
{
private:
	static bool instanceFlag;
	static GameScene* instance;
	GameScene() { }

	sf::Music m_backgroundMusic;
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