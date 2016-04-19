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
	rabbitNum = 4;
	doeNum = 3;
	bearNum = 2;
	stagNum = 1;
	wolfNum = 4;

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
}

void GameScene::Update()
{
	Player::GetInstance()->Update();
	CheckMouseCollision();

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
		if (Collision::PixelPerfectTest(Player::GetInstance()->GetPawSprite(), c->GetSprite()) && InputManager::GetInstance()->IsMouseButtonDown(0))
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
			//c->smellDetected = false;
		}
	}
}

void GameScene::CheckLevelChange()
{
	/*Check if player collides with level switch 
	{
		level switch.getID()
		m_map = new tmx::TileMap("Assets/Tiled/"+std::to_string(levelswitch.getID()+".tmx");
		if (Player::GetInstance()->GetPosition() != levelSwitch.getSpawn(levelSwitch.GetID()
			Player::GetInstance()->SetPosition(levelSwitch.getSpawn(levelSwitch.GetID());
	}*/
	
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