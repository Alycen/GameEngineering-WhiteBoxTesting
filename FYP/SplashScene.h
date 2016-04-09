#ifndef _SPLASHSCENE_
#define _SPLASHSCENE_

#include "SFML\Graphics.hpp"

class SplashScene
{
private:
	static bool instanceFlag;
	static SplashScene* instance;

	SplashScene() {};

	float ttl;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	static SplashScene* GetInstance();
	void Init();
	void Update();
	void Draw(sf::RenderWindow&);
};

#endif