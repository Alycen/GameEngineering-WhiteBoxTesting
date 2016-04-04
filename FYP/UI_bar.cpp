#include "UI_bar.h"

UI_bar::UI_bar()
{

}

UI_bar::UI_bar(float x, float y, string type, float legnth)
{
	//m_left_pos.y = y;
	//m_mid_pos.y = y;
	//m_right_pos.y = y;

	m_mid_pos.x = 10;
	m_right_pos.x = 164;

	m_left_tex.loadFromFile("Assets/UI/bar_left.png");
	m_mid_tex.loadFromFile("Assets/UI/bar_mid.png");
	m_right_tex.loadFromFile("Assets/UI/bar_right.png");

	m_left_filling_tex.loadFromFile("Assets/UI/" + type + "_left.png");
	m_mid_filling_tex.loadFromFile("Assets/UI/" + type + "_mid.png");
	m_right_filling_tex.loadFromFile("Assets/UI/" + type + "_right.png");

	m_left_sprite.setTexture(m_left_tex);
	m_left_sprite.setScale(.1, .1);
	m_mid_sprite.setTexture(m_mid_tex);
	m_mid_sprite.setScale(7, .1);
	m_right_sprite.setTexture(m_right_tex);
	m_right_sprite.setScale(.1, .1);

	m_left_filling_sprite.setTexture(m_left_filling_tex);

	m_mid_filling_sprite.setTexture(m_mid_filling_tex);

	m_right_filling_sprite.setTexture(m_right_filling_tex);


	isVisible = true;
}

void UI_bar::Update()
{
	m_left_sprite.setPosition(m_left_pos);
	m_mid_sprite.setPosition(m_mid_pos);
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