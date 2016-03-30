#include "GameScene.h"

bool GameScene::instanceFlag = false;
GameScene* GameScene::instance = NULL;

GameScene* GameScene::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new GameScene();
		instanceFlag = true;
		return instance;
	}
	else 
	{
		return instance;
	}
}

void GameScene::Init()
{
	if (!m_backgroundMusic.openFromFile("Assets/Audio/backGround.ogg"))
	{
		// handle error
	}
	m_map = new tmx::TileMap("Assets/Tiled/test.tmx");

	m_backgroundMusic.setVolume(10);
	//m_backgroundMusic.play();
	//m_backgroundMusic.setLoop(true);

	Player::GetInstance()->Init(3000,2500);
	Camera::GetInstance()->Init(1400,900);
	testKanine = new Kanine(700,400);
}

void GameScene::Update()
{
	Player::GetInstance()->Update();
	testKanine->Update();
	
	// check player doesnt leave bounding area
}

void GameScene::Draw(sf::RenderWindow &win)
{
	win.draw(*m_map);
	Player::GetInstance()->Draw(win);
	testKanine->Draw(win);
}