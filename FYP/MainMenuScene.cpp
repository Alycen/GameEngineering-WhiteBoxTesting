#include "MainMenuScene.h"
#include "SceneManager.h"

bool MainMenuScene::instanceFlag = false;
MainMenuScene* MainMenuScene::instance = NULL;

MainMenuScene* MainMenuScene::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new MainMenuScene();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void MainMenuScene::Init()
{
	gameSelected = false;
	settingsSelected = false;
	exitSelected = false;

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	if (!m_font.loadFromFile("Assets/Fonts/VINERITC.TTF")) 
	{
		//handle error
	}
	m_menu[0].setFont(m_font);
	m_menu[0].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[0].setStyle(sf::Text::Bold);
	m_menu[0].setColor(sf::Color::Cyan);
	m_menu[0].setString("Play");
	//m_menu[0].setPosition(sf::Vector2f(desktop.width / 6 , (desktop.height / 2) / (NUM_OF_ELEMENTS + 1) * 1));
	m_menu[0].setPosition(sf::Vector2f(200 / 2, 400 / (NUM_OF_ELEMENTS + 1) * 1));

	m_menu[1].setFont(m_font);
	m_menu[1].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[1].setStyle(sf::Text::Bold);
	m_menu[1].setColor(sf::Color::White);
	m_menu[1].setString("Settings");
	//m_menu[1].setPosition(sf::Vector2f(desktop.width / 6, (desktop.height / 2) / (NUM_OF_ELEMENTS + 1) * 2.5));
	m_menu[1].setPosition(sf::Vector2f(200 / 2, 400 / (NUM_OF_ELEMENTS + 1) * 2.5));

	m_menu[2].setFont(m_font);
	m_menu[2].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[2].setStyle(sf::Text::Bold);
	m_menu[2].setColor(sf::Color::White);
	m_menu[2].setString("Exit");
	//m_menu[2].setPosition(sf::Vector2f(desktop.width / 6, (desktop.height / 2) / (NUM_OF_ELEMENTS + 1) * 4));
	m_menu[2].setPosition(sf::Vector2f(200 / 2, 400 / (NUM_OF_ELEMENTS + 1) * 4));

	m_menu[3].setFont(m_font);
	m_menu[3].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[3].setStyle(sf::Text::Bold);
	m_menu[3].setColor(sf::Color::White);
	m_menu[3].setString("New Game");
	m_menu[3].setPosition(sf::Vector2f(200 / 2, 400 / (NUM_OF_ELEMENTS + 1) * 1));

	m_menu[4].setFont(m_font);
	m_menu[4].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[4].setStyle(sf::Text::Bold);
	m_menu[4].setColor(sf::Color::White);
	m_menu[4].setString("Load Game");
	m_menu[4].setPosition(sf::Vector2f(200 / 2, 400 / (NUM_OF_ELEMENTS + 1) * 2.5));

	m_menu[5].setFont(m_font);
	m_menu[5].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[5].setStyle(sf::Text::Bold);
	m_menu[5].setColor(sf::Color::White);
	m_menu[5].setString("Back");
	m_menu[5].setPosition(sf::Vector2f(200 / 2, 400 / (NUM_OF_ELEMENTS + 1) * 4));

	m_selectedItemIndex = 0;
	
	m_logoTexture.loadFromFile("Assets/Graphics/Menu/logo.png");
	m_logoTexture.setSmooth(true);

	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(sf::Vector2f(desktop.width / 2, 100));
}

void MainMenuScene::Update()
{
	if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::W) || InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::Up))
	{
		MoveUp();
	}
	else if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::S) || InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::Down))
	{
		MoveDown();
	}

	if (InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::Return) || InputManager::GetInstance()->IsKeyReleased(sf::Keyboard::Space))
	{
		switch (GetPressedItem())
		{
		case 0:
			m_selectedItemIndex = 3;
			first_scene = false;
			//settingsSelected = false;
			break;
		case 1:
			//settingsSelected = true;
			//gameSelected = false;
			break;
		case 2:
			cout << "EXIT PRESSED" << endl;
			exitSelected = true;
			break;
		case 3:
			cout << "NEW GAME PRESSED" << endl;
			gameSelected = true;
			//SceneManager::GetInstance()->m_currentScene = 2;
			break;
		case 4:
			cout << "LOAD GAME PRESSED" << endl;
			break;
		case 5:
			cout << "BACK PRESSED" << endl;
			m_selectedItemIndex = 0;
			first_scene = true;
			break;
		}
	}
}

void MainMenuScene::Draw(sf::RenderWindow &win)
{
	// restore the default view
	//win.setView(win.getDefaultView());
	if (first_scene)
	{
		for (int i = 0; i < 3; i++) 
		{
			win.draw(m_menu[i]);
		}
	}
	else if (!first_scene)
	{
		for (int i = 3; i < 6; i++)
		{
			win.draw(m_menu[i]);
		}
	}
	win.draw(m_logoSprite);
}

void MainMenuScene::MoveUp()
{
	if (first_scene)
	{
		if (m_selectedItemIndex - 1 >= 0) 
		{
			m_menu[m_selectedItemIndex].setColor(sf::Color::White);
			m_selectedItemIndex--;
			m_menu[m_selectedItemIndex].setColor(sf::Color::Cyan);
		}
	}
	else
	{
		if (m_selectedItemIndex - 1 >= 3)
		{
			m_menu[m_selectedItemIndex].setColor(sf::Color::White);
			m_selectedItemIndex--;
			m_menu[m_selectedItemIndex].setColor(sf::Color::Cyan);
		}
	}
}

void MainMenuScene::MoveDown()
{
	if (first_scene)
	{
		if (m_selectedItemIndex + 1 < 3) 
		{
			m_menu[m_selectedItemIndex].setColor(sf::Color::White);
			m_selectedItemIndex++;
			m_menu[m_selectedItemIndex].setColor(sf::Color::Cyan);
		}
	}
	else 
	{
		if (m_selectedItemIndex + 1 < 6)
		{
			m_menu[m_selectedItemIndex].setColor(sf::Color::White);
			m_selectedItemIndex++;
			m_menu[m_selectedItemIndex].setColor(sf::Color::Cyan);
		}
	}
}

int MainMenuScene::GetPressedItem() { return m_selectedItemIndex; }