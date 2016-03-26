#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Xinput.h>

class Gamepad
{
public:
	Gamepad();
	Gamepad(int);

private:
	XINPUT_STATE m_State; 
	int m_gamepadIndex;  
};

#endif