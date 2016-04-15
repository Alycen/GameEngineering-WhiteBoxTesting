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
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void SplashScene::Update() {}

void SplashScene::Draw(sf::RenderWindow &win)
{
	win.setView(win.getDefaultView());
	m_sprite.setPosition((win.getView().getSize().x / 2) + (m_texture.getSize().x / 25), (win.getView().getSize().x / 2) - (m_texture.getSize().y / 2)); // Need to make this scale more efficiently
	
	win.draw(m_sprite);
}