#ifndef _CAMERA_
#define _CAMERA_

#include "SFML\Graphics.hpp"

class Camera
{
private:
	static bool instanceFlag;
	static Camera* instance;
	sf::View camView;
	Camera()
	{
	}
public:
	static Camera* GetInstance();
	~Camera()
	{
		delete instance;
		instanceFlag = false;
	}
	void Init(int w, int h);
	void setCentre(sf::Vector2f pos);
	sf::View getView();
	void setView(sf::View v);
	void setViewPosition(sf::Vector2f pos);

	int window_height;
	int window_width;
	sf::VideoMode desktop;
};

#endif