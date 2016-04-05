#ifndef _MAINMENUSCENE_
#define _MAINMENUSCENE_

#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include "InputManager.h"
#include <iostream>

#define NUM_OF_ELEMENTS 6

using namespace std;

class MainMenuScene 
{
private:
	static bool instanceFlag;
	static MainMenuScene* instance;

	int m_selectedItemIndex;
	sf::Font m_font;
	sf::Text m_menu[NUM_OF_ELEMENTS];

	MainMenuScene() {}

	sf::Texture m_logoTexture;
	sf::Sprite m_logoSprite;
	bool first_scene = true;
public:
	bool gameSelected, settingsSelected, exitSelected;

	static MainMenuScene* GetInstance();

	void Init();
	void Update();
	void Draw(sf::RenderWindow&);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();	

	MainMenuScene::~MainMenuScene()
	{
		delete instance;
		instanceFlag = false;
	}
};

#endif