#include "UI_bar.h"

UI_bar::UI_bar()
{

}

UI_bar::UI_bar(float x, float y, string type, float legnth)
{

}

void UI_bar::Update()
{
	m_left_sprite.setPosition(m_left_pos);
	m_mid_sprite.setPosition(m_mid_pos);
	m_mid_sprite.setScale(1, m_length);
	m_right_sprite.setPosition(m_right_pos);
}

void UI_bar::Draw(sf::RenderWindow &win)
{
	if (isVisible)
	{
		win.draw(m_left_sprite);
		win.draw(m_mid_sprite);
		win.draw(m_right_sprite);
	}
	else
	{
		// do nothing
	}
}

// Lenght
void UI_bar::SetLength(float length)
{

}

float UI_bar::GetLength()
{
	return m_length;
}

// Position
void UI_bar::SetPosition(float x, float y)
{
	m_left_pos = sf::Vector2f(x, y);
}

sf::Vector2f UI_bar::GetPosition()
{
	return m_left_pos;
}

float UI_bar::GetX()
{
	return m_left_pos.x;
}

float UI_bar::GetY()
{
	return m_left_pos.y;
}