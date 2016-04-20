#ifndef _INGAMEMENU_
#define _INGAMEMENU_

#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include "InputManager.h"

#define NUM_ELEMENTS 4

class InGameMenu
{
private:
	static bool instanceFlag;
	static InGameMenu* instance;

	int m_selectedItemIndex;
	sf::Font m_font;
	sf::Text m_menu[NUM_ELEMENTS];

	InGameMenu() {}

	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	bool backSelected;

	static InGameMenu* GetInstance();

	void Init();
	void Update();
	void Draw(sf::RenderWindow&);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

	InGameMenu::~InGameMenu()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif