#include "Gamepad.h"

#pragma comment(lib, "Xinput.lib");

Gamepad::Gamepad() {}

Gamepad::Gamepad(int index)
{
	m_gamepadIndex = index - 1;
}