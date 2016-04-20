#include "InGameMenu.h"
#include "SceneManager.h"

bool InGameMenu::instanceFlag = false;
InGameMenu* InGameMenu::instance = NULL;

InGameMenu* InGameMenu::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new InGameMenu();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void InGameMenu::Init()
{
	backSelected = false;

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	if (!m_font.loadFromFile("Assets/Fonts/VINERITC.TTF"))
	{
		//handle error
	}
	m_menu[0].setFont(m_font);
	m_menu[0].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[0].setStyle(sf::Text::Bold);
	m_menu[0].setColor(sf::Color::Cyan);
	m_menu[0].setString("Resume");
	m_menu[0].setPosition(sf::Vector2f((desktop.width / 2) - 200, desktop.height / (NUM_ELEMENTS + 1) * 1));

	m_menu[1].setFont(m_font);
	m_menu[1].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[1].setStyle(sf::Text::Bold);
	m_menu[1].setColor(sf::Color::White);
	m_menu[1].setString("Save");
	m_menu[1].setPosition(sf::Vector2f((desktop.width / 2) - 200, desktop.height / (NUM_ELEMENTS + 1) * 1.75));

	m_menu[2].setFont(m_font);
	m_menu[2].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[2].setStyle(sf::Text::Bold);
	m_menu[2].setColor(sf::Color::White);
	m_menu[2].setString("MainMenu");
	m_menu[2].setPosition(sf::Vector2f((desktop.width / 2) - 200, desktop.height / (NUM_ELEMENTS + 1) * 2.5));

	m_menu[3].setFont(m_font);
	m_menu[3].setScale(sf::Vector2f(1.5, 1.5));
	m_menu[3].setStyle(sf::Text::Bold);
	m_menu[3].setColor(sf::Color::White);
	m_menu[3].setString("Exit Game");
	m_menu[3].setPosition(sf::Vector2f((desktop.width / 2) - 200, desktop.height / (NUM_ELEMENTS + 1) * 3.25));

	m_selectedItemIndex = 0;

	m_texture.loadFromFile("Assets/Graphics/Menu/inGameFilter.png");
	m_texture.setSmooth(true);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(sf::Vector2f(desktop.width / 2, desktop.height / 2));
}

void InGameMenu::Update()
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
			cout << "Resume" << endl;
			SceneManager::GetInstance()->SetScene(2);
			break;
		case 1:
			cout << "Save" << endl;
			backSelected = false;
			break;
		case 2:
			cout << "Main Menu" << endl;
			SceneManager::GetInstance()->SetScene(1);
			break;
		case 3:
			cout << "Exit Game" << endl;
			MainMenuScene::GetInstance()->exitSelected = true;
			break;
		}
	}
}

void InGameMenu::Draw(sf::RenderWindow &win)
{
	win.draw(m_sprite);
	for (int i = 0; i < NUM_ELEMENTS; i++)
	{
		win.draw(m_menu[i]);
	}
}

void InGameMenu::MoveUp()
{
	if (m_selectedItemIndex - 1 >= 0) 
	{
		m_menu[m_selectedItemIndex].setColor(sf::Color::White);
		m_selectedItemIndex--;
		m_menu[m_selectedItemIndex].setColor(sf::Color::Cyan);
	}
}

void InGameMenu::MoveDown()
{
	if (m_selectedItemIndex + 1 < NUM_ELEMENTS)
	{
		m_menu[m_selectedItemIndex].setColor(sf::Color::White);
		m_selectedItemIndex++;
		m_menu[m_selectedItemIndex].setColor(sf::Color::Cyan);
	}
}

int InGameMenu::GetPressedItem() { return m_selectedItemIndex; }