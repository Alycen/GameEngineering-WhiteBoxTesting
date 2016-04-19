#include "SceneManager.h"

bool SceneManager::instanceFlag = false;
SceneManager* SceneManager::instance = NULL;

int SPLASH = 0, MAIN = 1, GAME = 2, INGAMEMENU = 3;

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
	MainMenuScene::GetInstance()->Init();
	GameScene::GetInstance()->Init();
	InGameMenu::GetInstance()->Init();
	
	if (!m_backgroundMusic.openFromFile("Assets/Audio/Background/mystic.ogg"))
	{
		// handle error
	}

	m_backgroundMusic.setVolume(20);
	m_backgroundMusic.play();
	m_backgroundMusic.setLoop(true);
}

void SceneManager::Update()
{
	if (MainMenuScene::GetInstance()->gameSelected)
		m_currentScene = GAME;

	else if (m_spashSceneTimer <= 0)
	{
		m_currentScene = MAIN;
		//SplashScene::GetInstance()->~SplashScene();
	}
	else
	{
		m_spashSceneTimer--;
	}

	switch (GetScene())
	{
	case 0:
		SplashScene::GetInstance()->Update();
		break;
	case 1:
		//InGameMenu::GetInstance()->Update();
		MainMenuScene::GetInstance()->Update();
		break;
	case 2:
		GameScene::GetInstance()->Update();
		break;
	case 3:
		//
		break;
	}
}

void SceneManager::Draw(sf::RenderWindow &win)
{
	if (m_currentScene == 0)
	{
		SplashScene::GetInstance()->Draw(win);
	}
	else if (m_currentScene == 1)
	{
		//InGameMenu::GetInstance()->Draw(win);
		MainMenuScene::GetInstance()->Draw(win);
	}
	else if (m_currentScene == 2)
	{
		GameScene::GetInstance()->Draw(win);
		win.setView(Camera::GetInstance()->getView());
	}
}