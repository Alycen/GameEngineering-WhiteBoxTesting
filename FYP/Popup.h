#ifndef _POPUP_
#define _POPUP_

#include "SFML\Graphics.hpp"

class Popup
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	
	sf::Vector2f m_position;

	float ttl, m_value, m_size;
public:
	Popup();
	Popup(float, float);

	void Init(float, float);
	void Update();
	void Update(sf::Vector2f);
	void Draw(sf::RenderWindow&);
};

#endif