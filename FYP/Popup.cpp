#include "Popup.h"

Popup::Popup() 
{
	m_texture.loadFromFile("Assets/UI/PopupO.png");
	m_texture.setSmooth(true);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setRotation(0);
}

Popup::Popup(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_texture.loadFromFile("Assets/UI/PopupO.png");
	m_texture.setSmooth(true);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setRotation(0);
}

void Popup::Init(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Popup::Update() 
{
	m_sprite.setPosition(m_position);
}

void Popup::Update(sf::Vector2f origin)
{
	m_position = origin;
	m_sprite.setPosition(m_position);
}

void Popup::Draw(sf::RenderWindow &win)
{
	win.draw(m_sprite);
}