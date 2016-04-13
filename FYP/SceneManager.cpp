#include "SceneManager.h"

bool SceneManager::instanceFlag = false;
SceneManager* SceneManager::instance = NULL;

int SPLASH = 0, MAIN = 1, GAME = 2;

SceneManager* SceneManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new SceneManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void SceneManager::Init()
{
	m_currentScene = SPLASH;
	SplashScene::GetInstance()->Init();
}

void SceneManager::Update()
{
	if (m_spashSceneTimer <= 0)
	{
		m_currentScene = MAIN;
		MainMenuScene::GetInstance()->Init();
		//SplashScene::GetInstance()->~SplashScene();
	}
	else
	{
		m_spashSceneTimer--;
	}

	switch (GetScene())
	{
	case 0:
		//cout << "Current Scene : SPLASH" << endl;
		SplashScene::GetInstance()->Update();
		break;
	case 1:
		//cout << "Current Scene : MAIN MENU" << endl;
		MainMenuScene::GetInstance()->Update();
		break;
	case 2:
		//cout << "Current Scene : GAME" << endl;

		break;
	}
}

void SceneManager::Draw(sf::RenderWindow &win)
{
	if (m_currentScene == 0)
	{
		// restore the default view
		win.setView(win.getDefaultView());
		SplashScene::GetInstance()->Draw(win);
	}
	else if (m_currentScene == 1)
	{
		// restore the default view
		win.setView(win.getDefaultView());
		MainMenuScene::GetInstance()->Draw(win);
	}
	else if (m_currentScene == 2)
	{
		//GameScene::GetInstance()->Draw(win);
	}
}