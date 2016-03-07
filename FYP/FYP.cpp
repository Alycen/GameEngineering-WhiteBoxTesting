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

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1400, 900, 32), "FYP");
	Player::GetInstance()->Init(700, 450);

	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			InputManager::GetInstance()->UpdatePolledEvents(Event);
			if (Event.type == sf::Event::Closed)
				window.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		Player::GetInstance()->Update();
		InputManager::GetInstance()->UpdateState();
		
		window.clear();
		Player::GetInstance()->Draw(window);
		//window.setView(Camera::GetInstance()->getView());
		window.display();
	}

	return EXIT_SUCCESS;
}

