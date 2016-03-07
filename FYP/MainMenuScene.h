#ifndef _MAINMENUSCENE_
#define _MAINMENUSCENE_

#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include "InputManager.h"
#include <iostream>

#define NUM_OF_ELEMENTS 3

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
public:
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