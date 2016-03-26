#ifndef _GAMEPAD_
#define _GAMEPAD_

#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib") 

class Gamepad
{
public:
	Gamepad();
	~Gamepad();

	bool CheckControllerConnection(bool showOutput);
	void Rumble(int leftMotorRumble, int rightMotorRumble);

	void CheckAllButtons();

	void CheckADown();
	void CheckBDown();
	void CheckXDown();
	void CheckYDown();

	void CheckDpadUp();
	void CheckDpadDown();
	void CheckDpadRight();
	void CheckDpadLeft();

	void CheckRB();
	void CheckLB();

	void CheckStart();
	void CheckBack();

	void CheckRT();
	void CheckLT();

	void leftStickMovement();

	bool A() { return aPressed; }
	bool B() { return bPressed; }
	bool X() { return xPressed; }
	bool Y() { return yPressed; }

	bool DpadUp() { return upPressed; }
	bool DpadDown() { return downPressed; }
	bool DpadRight() { return rightPressed; }
	bool DpadLeft() { return leftPressed; }

	bool RB() { return rbPressed; }
	bool LB() { return lbPressed; }

	bool Start() { return startPressed; }
	bool Back() { return backPressed; }

	bool RT() { return rtPressed; }
	bool LT() { return ltPressed; }

	sf::Vector2f getNormalisedLeftStickAxis() { return normalisedLeftStickAxis; }
	bool isLeftAxisOutOfDeadzone() { return leftStickOutOfDeadzone; }

private:
	XINPUT_STATE state;
	XINPUT_VIBRATION motor;

	//a,b,x,y
	bool aPressed;
	bool bPressed;
	bool xPressed;
	bool yPressed;
	//d-pad
	bool upPressed;
	bool downPressed;
	bool rightPressed;
	bool leftPressed;
	//shoulder buttons
	bool lbPressed;
	bool rbPressed;
	//start and back/menu and view
	bool startPressed;
	bool backPressed;

	//triggers
	bool rtPressed;
	bool ltPressed;

	//left trigger
	sf::Vector2f leftStickAxis;
	sf::Vector2f normalisedLeftStickAxis;
	float leftStickMagnitude;
	float normalisedLeftStickMagnitude;

	bool leftStickOutOfDeadzone;
};

#endif