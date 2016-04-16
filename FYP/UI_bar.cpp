#include "UI_bar.h"

UI_bar::UI_bar() { }

UI_bar::UI_bar(float y, string type, float legnth)
{
	m_length = 100;
	m_scale = .12f;
	m_y = y;
	//m_fillingScale = 20.0f;

	m_left_tex.loadFromFile("Assets/UI/bar_left.png");
	m_mid_tex.loadFromFile("Assets/UI/bar_mid.png");
	m_right_tex.loadFromFile("Assets/UI/bar_right.png");

	m_left_filling_tex.loadFromFile("Assets/UI/" + type + "_left.png");
	m_mid_filling_tex.loadFromFile("Assets/UI/" + type + "_mid.png");
	m_right_filling_tex.loadFromFile("Assets/UI/" + type + "_right.png");

	m_left_sprite.setTexture(m_left_tex);
	m_left_sprite.setScale(m_scale, m_scale);
	m_mid_sprite.setTexture(m_mid_tex);
	m_mid_sprite.setScale(20, m_scale);
	m_right_sprite.setTexture(m_right_tex);
	m_right_sprite.setScale(m_scale, m_scale);

	m_left_filling_sprite.setTexture(m_left_filling_tex);
	m_left_filling_sprite.setScale(m_scale, m_scale);
	m_mid_filling_sprite.setTexture(m_mid_filling_tex);
	m_mid_filling_sprite.setScale(20, m_scale);
	m_right_filling_sprite.setTexture(m_right_filling_tex);
	m_right_filling_sprite.setScale(m_scale, m_scale);

	isVisible = true;
}

void UI_bar::Update()
{
	//if (m_fillingScale >=0 )
	//{
	//}

	m_left_sprite.setPosition(m_left_pos);
	m_mid_sprite.setPosition(m_mid_pos);
	m_right_sprite.setPosition(m_right_pos);

	m_left_filling_sprite.setPosition(m_left_filling_pos);
	m_mid_filling_sprite.setPosition(m_mid_filling_pos);
	m_right_filling_sprite.setPosition(m_right_filling_pos);

	m_mid_filling_sprite.setScale(m_fillingScale, m_scale);
}

void UI_bar::Draw(sf::RenderWindow &win)
{
	sf::Vector2f windowCentre = win.getView().getCenter();
	sf::Vector2f windowSize = win.getView().getSize();

	//Leave border positions as is
	m_left_pos = sf::Vector2f(windowCentre.x - ((windowSize.x / 2) - 20), windowCentre.y - ((windowSize.y / 2) - m_y));
	m_mid_pos = sf::Vector2f(windowCentre.x - ((windowSize.x / 2) - 33), windowCentre.y - ((windowSize.y / 2) - m_y));
	m_right_pos = sf::Vector2f(windowCentre.x - (m_length * 2.3), windowCentre.y - ((windowSize.y / 2) - m_y));

	// Need modifiable Length variable for here
	m_left_filling_pos = sf::Vector2f(windowCentre.x - ((windowSize.x / 2) - 22), windowCentre.y - ((windowSize.y / 2) - m_y));
	//Below needs modifying
	m_mid_filling_pos = sf::Vector2f(windowCentre.x - ((windowSize.x / 2.01) - 30), windowCentre.y - ((windowSize.y / 2) - m_y));
	m_right_filling_pos = sf::Vector2f(windowCentre.x - (m_length * 2.3), windowCentre.y - ((windowSize.y / 2) - m_y));

	if (isVisible)
	{
		win.draw(m_left_filling_sprite);
		win.draw(m_mid_filling_sprite);
		win.draw(m_right_filling_sprite);

		win.draw(m_left_sprite);
		win.draw(m_mid_sprite);
		win.draw(m_right_sprite);
	}
	else
	{
		// do nothing
	}
}

void UI_bar::Decrease(float v)
{
	
}

void UI_bar::Increase(float v)
{

}         

float UI_bar::GetValue() 
{
	return m_fillingScale;
}

void UI_bar::SetValue(float v)
{
	m_fillingScale = v;
}