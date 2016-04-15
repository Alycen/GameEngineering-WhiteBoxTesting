#ifndef _SCENEMANAGER_
#define _SCENEMANAGER_

#include "SplashScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"

class SceneManager
{
private:
	static bool instanceFlag;
	static SceneManager* instance;

	SceneManager() {};

	int m_spashSceneTimer = 100;
public:
	static SceneManager* GetInstance();
	void Init();
	void Update();
	void Draw(sf::RenderWindow&);

	int m_currentScene;

	void SceneManager::SetScene(int scene) { m_currentScene = scene; }
	int SceneManager::GetScene() { return m_currentScene; }

};

#endif