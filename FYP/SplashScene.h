#ifndef _SPLASHSCENE_
#define _SPLASHSCENE_

#include "SFML\Graphics.hpp"

class SplashScene
{
private:
	static bool instanceFlag;
	static SplashScene* insta

	float ttl;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	SplashScene::SplashScene()
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
	SplashScene::Init()
	{
		m_texture.loadFromFile("Assets/Graphics/Splash/Splash.png");
		m_texture.setSmooth(true);

		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(m_texture.getSize().x / 3, m_texture.getSize().y / 4);
	}
};

#endif