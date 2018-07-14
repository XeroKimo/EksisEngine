#pragma once

#include <windows.h>
#include <map>

#include "EKeyCodes.h"

#define KEY_ERROR -1
#define KEY_INACTIVE 0
#define KEY_DOWN 1
#define KEY_UP 2
#define KEY_HELD 3

class EController
{
protected:
	std::map<EKeyCode, int> m_keyMap;
	std::map<EKeyCode, int> m_previousKeyMap;
public:
	std::map<EKeyCode, int> PollInput();
	std::map<EKeyCode, int> GetMap();
	bool IsKeyValid(EKeyCode);

	int GetPressed(EKeyCode);
	int GetState(EKeyCode);
};
