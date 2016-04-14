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
	testKanine = new Kanine(2700, 2700);
	testBear = new Bear(2900, 2700);
	testStag = new Stag(2800, 2700);
	bambisMom = new Doe(2600, 2700);
	testBunny = new Rabbit(2500, 2700);

	temp_healtbar = new UI_bar(20, "Health", Player::GetInstance()->GetHealth()); 
	temp_staminabar = new UI_bar(50, "Stamina", Player::GetInstance()->GetHealth());
}

void GameScene::Update()
{
	Player::GetInstance()->Update();
	testKanine->Update();
	testBear->Update(Player::GetInstance()->GetPosition());
	testStag->Update(Player::GetInstance()->GetPosition());
	bambisMom->Update(Player::GetInstance()->GetPosition());
	testBunny->Update(Player::GetInstance()->GetPosition());

	Player::GetInstance()->SetSelectedNPC(testBear->GetPosition());

	temp_healtbar->Update();
	temp_staminabar->Update();
	// check player doesnt leave bounding area
}

void GameScene::Draw(sf::RenderWindow &win)
{
	win.draw(*m_map);
	testKanine->Draw(win);
	testBear->Draw(win);
	testStag->Draw(win);
	bambisMom->Draw(win);
	testBunny->Draw(win);

	Player::GetInstance()->Draw(win);

	// restore the default view
	win.setView(win.getDefaultView());

	temp_healtbar->Draw(win);
	temp_staminabar->Draw(win);
}