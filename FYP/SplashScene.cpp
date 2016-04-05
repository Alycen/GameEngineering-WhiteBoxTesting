#include "SplashScene.h"

bool SplashScene::instanceFlag = false;
SplashScene* SplashScene::instance = NULL;

SplashScene* SplashScene::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new SplashScene();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void SplashScene::Init()
{
	m_texture.loadFromFile("Assets/Graphics/Splash/Splash.png");
	m_texture.setSmooth(true);

	m_sprite.setTexture(m_texture);
}

void SplashScene::Update() {}

void SplashScene::Draw(sf::RenderWindow &win)
{
	m_sprite.setPosition(win.getSize().x / 1.5, win.getSize().y / 1.5);
	win.draw(m_sprite);
}