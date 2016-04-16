#ifndef _UI_BAR_
#define _UI_BAR_

#include "stdafx.h"
#include "Camera.h"

class UI_bar
{
private:
	//Border
	sf::Vector2f m_left_pos;
	sf::Vector2f m_right_pos;
	sf::Vector2f m_mid_pos;

	sf::Texture m_left_tex;
	sf::Texture m_right_tex;
	sf::Texture m_mid_tex;

	sf::Sprite m_left_sprite;
	sf::Sprite m_right_sprite;
	sf::Sprite m_mid_sprite;

	string m_type;
	float m_length;
	float m_scale;
	float m_y;
	float m_fillingScale;

	// Filling
	sf::Vector2f m_left_filling_pos;
	sf::Vector2f m_right_filling_pos;
	sf::Vector2f m_mid_filling_pos;

	sf::Texture m_left_filling_tex;
	sf::Texture m_right_filling_tex;
	sf::Texture m_mid_filling_tex;

	sf::Sprite m_left_filling_sprite;
	sf::Sprite m_right_filling_sprite;
	sf::Sprite m_mid_filling_sprite;
	
	bool isVisible;
public:
	UI_bar();
	UI_bar(float, string, float); // float x, float y, int type (health / stamina), float length

	void Update();
	void Draw(sf::RenderWindow&);

	// set / get length of bar
	void SetLength(float l) { m_length = l; };
	float GetLength() { return m_length; };

	void Decrease(float);
	void Increase(float);
	float GetValue();
	void SetValue(float);
	float GetMaxVal() { return 20.0f; }

	// get / set isVisible
	void SetVisible(bool v) { isVisible = v; }
	bool GetVisible() {return isVisible; }

};

#endif