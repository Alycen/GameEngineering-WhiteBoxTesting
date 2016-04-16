#include "stdafx.h"
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML\Graphics.hpp"
#include "SFML/OpenGL.hpp" 
#include "InputManager.h"
#include "Player.h"
#include "Camera.h"
#include "STP\TMXLoader.hpp"
#include "SceneManager.h"

// -----------------------------------------|
// TO DO:									|
// -----------------------------------------|
// Sound							|	 1 h|
// ---Scene Manager	---				|	 ---|
// Settings							|	 2 h|
// Interaction with NPCs			|	 3 h|
// Particles						|	 2 h|
// Popups							|	 1 h|
// ---NPC AI---						|	 ---|
// -> Attack						|	 2 h|
// Player stay within level bounds	|	 2 h|
// ---Player Stats---				|	 ---|
// Level switch						|	 2 h|
// Load / Save Level				|	 8 h|
// ---Targetting---					|	 ---|
// Select NPC						|    4 h|
// LOAD SCENE!!!!!!!!				|	 1 h|
// -----------------------------------------|
//											|
// AI Behaviours 						    |
// -> Move() - Wander						|
// -> Stare() - Rotate towards, dont move	|		
// -> Follow() - Slowly follow				|
// -> Chase() - Quickly follow				|
// -> Avoid() - Slowly avoid				|
// -> Flee() - quickly avoid				|
// -> Attack() - cause damage				|
// Dont go outside the level bounds			|
// -----------------------------------------|

int main()
{
	srand(time(NULL));
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	//sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "Beasts of Burden", sf::Style::None);
	sf::RenderWindow window(sf::VideoMode(1400, 900, 32), "FYP");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	SceneManager::GetInstance()->Init();

	while (window.isOpen())
	{
		sf::Event Event;
		sf::Mouse mouse;
		window.setMouseCursorVisible(false);
		while (window.pollEvent(Event))
		{
			InputManager::GetInstance()->UpdatePolledEvents(Event);

			if (Event.type == sf::Event::Closed)
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				GameScene::GetInstance()->CheckMouseCollision();
			}
		}

		// *** UPDATES *** //
		SceneManager::GetInstance()->Update();
		if (MainMenuScene::GetInstance()->exitSelected)
		{
			window.close();
		}
		InputManager::GetInstance()->GetWindow(mouse, window);
		InputManager::GetInstance()->UpdateState();
		
		// *** DRAW *** //
		window.clear();
		SceneManager::GetInstance()->Draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}