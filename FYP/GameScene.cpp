#include "GameScene.h"
#include "SceneManager.h"

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
	rabbitNum = 4;

	m_map = new tmx::TileMap("Assets/Tiled/map" + to_string(level) + ".tmx");

	Player::GetInstance()->Init();
	Camera::GetInstance()->Init(1400,900);

	for (int i = 0; i < wolfNum; i++)
	{
		npcs.push_back(new Kanine(1000, 1000));
	}
	for (int i = 0; i < bearNum; i++)
	{
		npcs.push_back(new Bear(2000, 2000));
	}
	for (int i = 0; i < stagNum; i++)
	{
		npcs.push_back(new Stag(3000, 3000));
	}
	for (int i = 0; i < doeNum; i++)
	{
		npcs.push_back(new Doe(3000, 3000));
	}
	for (int i = 0; i < rabbitNum; i++)
	{
		npcs.push_back(new Rabbit(4000, 4000));
	}

	m_healthbar = new UI_bar(20, "Health", Player::GetInstance()->GetHealth()); 
	m_staminabar = new UI_bar(50, "Stamina", Player::GetInstance()->GetStamina());

	m_levelExitTex.loadFromFile("Assets/Graphics/Actions/levelExit.png");
	
	m_levelExit1.setTexture(m_levelExitTex);
	m_levelExit2.setTexture(m_levelExitTex);
	m_levelExit3.setTexture(m_levelExitTex);
}

void GameScene::Update()
{
	Player::GetInstance()->Update();
	CheckMouseCollision();
	CheckLevelChange();

	if (level == 1)
	{
		m_levelExit1.setPosition(-1000, -1000);
		m_levelExit2.setPosition(40, 2500);
		m_levelExit3.setPosition(5250, 2500);

		m_map = new tmx::TileMap("Assets/Tiled/map" + to_string(level) + ".tmx");
	}
	else if (level == 2)
	{
		m_levelExit1.setPosition(5250, 2500);
		m_levelExit2.setPosition(-2000, -2000);
		m_levelExit3.setPosition(-1000, -1000);

		m_map = new tmx::TileMap("Assets/Tiled/map" + to_string(level) + ".tmx");
	}
	else if (level == 3)
	{
		m_levelExit1.setPosition(40, 2500);
		m_levelExit2.setPosition(-2000, -2000);
		m_levelExit3.setPosition(-1000, -1000);

		m_map = new tmx::TileMap("Assets/Tiled/map" + to_string(level) + ".tmx");
	}

	for each (Critter* c in npcs)
	{
		c->Update(Player::GetInstance()->GetPosition());
		if (c->m_selected)
		{
			Player::GetInstance()->SetSelectedNPC(c->GetPosition());
		}
	}

	UpdateHealth();
	UpdateStamina();

	m_healthbar->Update();
	m_staminabar->Update();
	
	if (Player::GetInstance()->isAttacking())
	{
		for each (Critter* c in npcs)
		{
			// 
		}
	}

	if (Player::GetInstance()->isAttacking())
	{
		CheckPlayerAttack();
	}

	// check player doesnt leave bounding area
	for each(Critter* c in npcs)
	{
		if (Collision::PixelPerfectTest(Player::GetInstance()->GetSprite(), c->GetSprite()))
		{
			//cout << "Player colliding" << endl;
		}
	}
}

void GameScene::Draw(sf::RenderWindow &win)
{
	win.draw(*m_map);
	for each (Critter* c in npcs)
	{
		c->Draw(win);
	}

	win.draw(m_levelExit1);
	win.draw(m_levelExit2);
	win.draw(m_levelExit3);

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

	m_healthbar->SetValue(value);
}

void GameScene::UpdateStamina()
{
	float playerCurrStamina = Player::GetInstance()->GetStamina();
	float playerStaminaFull = Player::GetInstance()->GetMaxStamina();

	//get the current percent of the players stamina
	float percent = (playerCurrStamina / playerStaminaFull) * 100;

	// find what value that perce nt is of the stamina bar
	float staminaBarFull = m_staminabar->GetMaxVal();
	float value = (staminaBarFull / 100) * percent;
	m_staminabar->SetValue(value);
}

// Collision Checks
void GameScene::CheckMouseCollision()
{
	for each(Critter* c in npcs)
	{
		if ((Collision::PixelPerfectTest(Player::GetInstance()->GetPawSprite(), c->GetSprite()) && InputManager::GetInstance()->IsMouseButtonDown(0)) && !c->m_dead)
		{
			for each(Critter* c1 in npcs) // Set all Critters in npcs list to false 
			{ // This means that if one Critter is selected and the player select a new target, it will swap to th new target
				c1->m_selected = false;
			}
			Player::GetInstance()->m_selected = true;
			c->m_selected = true;
		}
	}
}

void GameScene::CheckPlayerSmell()
{
	for each(Critter* c in npcs)
	{// Need to fix for when Player not smelling
		if (Collision::PixelPerfectTest(Player::GetInstance()->GetSmellSprite(), c->GetSprite()) && Player::GetInstance()->isSmelling())
		{
			//cout << "Can smell something" << endl;
			c->smellDetected = true;
		}
		else
		{
			c->smellDetected = false;
		}
	}
}

void GameScene::CheckLevelChange()
{
	// Check if the player is switching to level 1
	if (Collision::BoundingBoxTest(Player::GetInstance()->GetSprite(), m_levelExit1))
	{
		if (level == 2)
			Player::GetInstance()->SetPosition(sf::Vector2f(m_levelExit1.getPosition().x - 100, 2500));
		else
			Player::GetInstance()->SetPosition(sf::Vector2f(m_levelExit1.getPosition().x + 100, 2500));

		level = 1;

		wolfNum = 5;
		rabbitNum = 6;
	}
	// Check if the player is switching to level 2
	if (Collision::BoundingBoxTest(Player::GetInstance()->GetSprite(), m_levelExit2))
	{
		if (level == 1)
			Player::GetInstance()->SetPosition(sf::Vector2f(m_levelExit2.getPosition().x + 100, 2500));
		else
			Player::GetInstance()->SetPosition(sf::Vector2f(m_levelExit2.getPosition().x - 100, 2500));

		level = 2;

		bearNum = 5;
		rabbitNum = 4;
		doeNum = 3;
	}
	// Check if the player is switching to level 3
	if (Collision::BoundingBoxTest(Player::GetInstance()->GetSprite(), m_levelExit3))
	{
		if (level == 1)
			Player::GetInstance()->SetPosition(sf::Vector2f(m_levelExit2.getPosition().x - 100, 2500));
		else
			Player::GetInstance()->SetPosition(sf::Vector2f(m_levelExit2.getPosition().x + 100, 2500));

		level = 3;

		stagNum = 2;
		doeNum = 6;
		rabbitNum = 4;
	}
}

void GameScene::CheckPlayerAttack()
{
	for each(Critter* c in npcs)
	{
		if (Collision::BoundingBoxTest(Player::GetInstance()->GetAttackArea(), c->GetSprite()))
		{
			c->DecreaseHealth(Player::GetInstance()->GetAttackDamage());
		}
	}
}

void GameScene::Reset()
{
	Player::GetInstance()->Reset();
	npcs.clear();

	for (int i = 0; i < wolfNum; i++)
	{
		npcs.push_back(new Kanine(1000, 1000));
	}
	for (int i = 0; i < bearNum; i++)
	{
		npcs.push_back(new Bear(2000, 2000));
	}
	for (int i = 0; i < stagNum; i++)
	{
		npcs.push_back(new Stag(3000, 3000));
	}
	for (int i = 0; i < doeNum; i++)
	{
		npcs.push_back(new Doe(3000, 3000));
	}
	for (int i = 0; i < rabbitNum; i++)
	{
		npcs.push_back(new Rabbit(4000, 4000));
	}
}