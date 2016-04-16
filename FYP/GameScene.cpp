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

	//m_backgroundMusic.setVolume(10);
	//m_backgroundMusic.play();
	//m_backgroundMusic.setLoop(true);

	Player::GetInstance()->Init(3000,2500);
	Camera::GetInstance()->Init(1400,900);
	testKanine = new Kanine(2700, 2700);
	testBear = new Bear(2900, 2700);
	testStag = new Stag(2800, 2700);
	bambisMom = new Doe(2600, 2700);
	testBunny = new Rabbit(2500, 2700);

	m_healthbar = new UI_bar(20, "Health", Player::GetInstance()->GetHealth()); 
	m_staminabar = new UI_bar(50, "Stamina", Player::GetInstance()->GetStamina());

	m_healthbar->SetValue(20.0f);
	m_staminabar->SetValue(20.0f);
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

	UpdateHealth();
	UpdateStamina();

	m_healthbar->Update();
	m_staminabar->Update();

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

	m_healthbar->Draw(win);
	m_staminabar->Draw(win);
}

// UI bars
void GameScene::UpdateHealth()
{
	float playerCurrHealth = Player::GetInstance()->GetHealth();
	float playerHealthFull = Player::GetInstance()->GetMaxHealth();

	//get the current percent of the players health
	float percent = (playerCurrHealth / playerHealthFull) * 100;

	// find what value that percent is of the health bar
	float healthBarFull = m_healthbar->GetMaxVal();
	float value = (healthBarFull / 100) * percent;
	cout << value << endl;
	m_healthbar->SetValue(value);
}

void GameScene::UpdateStamina()
{
	float playerCurrStamina = Player::GetInstance()->GetStamina();
	float playerStaminaFull = Player::GetInstance()->GetMaxStamina();

	//get the current percent of the players stamina
	float percent = (playerStaminaFull / playerCurrStamina) * 100;

	// find what value that percent is of the stamina bar
	float staminaBarFull = m_staminabar->GetMaxVal();
	float value = (staminaBarFull / 100) * percent;
	m_healthbar->SetValue(value);
}