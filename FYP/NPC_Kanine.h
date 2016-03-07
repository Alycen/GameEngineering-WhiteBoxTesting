#ifndef _NPC_KANINE_
#define _NPC_KANINE_

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Pvector.h"

#define DistanceOfNeck 35.5

class Kanine
{
private:
	sf::Texture m_bodyTexture;
	sf::Texture m_headTexture;
	sf::Sprite m_bodySprite;
	sf::Sprite m_headSprite;

	Pvector m_position;
	Pvector m_direction;

	float m_rotation;
public:
	Kanine();
	Kanine(float, float);

	void Update();
	void Draw(sf::RenderWindow&);
	void Move();

	void SetPosition(Pvector pos) { m_position = pos; }
	Pvector GetPosition() { return m_position; }
	void SetX(float x) { m_position.x = x; }
	float GetX() { return m_position.x; }
	void SetY(float y) { m_position.y = y; }
	float GetY() { return m_position.y; }

	Kanine::~Kanine() {};
};

#endif