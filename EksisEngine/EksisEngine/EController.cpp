#include "EController.h"

std::map<EKeyCode, int> EController::PollInput()
{
	m_previousKeyMap = m_keyMap;

	for (const auto& pair : m_keyMap)
	{
		if (GetAsyncKeyState((int)pair.first))
		{
			m_keyMap[pair.first] = KEY_DOWN;
		}
		else
		{
			m_keyMap[pair.first] = KEY_INACTIVE;
		}
	}

	return m_keyMap;
}

std::map<EKeyCode, int> EController::GetMap()
{
	return m_keyMap;
}

bool EController::IsKeyValid(EKeyCode key)
{
	return (m_keyMap.find(key) != m_keyMap.end()) ? true : false;
}

int EController::GetPressed(EKeyCode key)
{
	return m_keyMap[key];
}

int EController::GetState(EKeyCode key)
{
	if (!IsKeyValid(key))
	{
		return KEY_ERROR;
	}

	if (m_keyMap[key] == KEY_DOWN && m_previousKeyMap[key] == KEY_INACTIVE)
	{
		return KEY_DOWN;
	}
	else if (m_keyMap[key] == KEY_DOWN && m_previousKeyMap[key] == KEY_DOWN)
	{
		return KEY_HELD;
	}
	else if (m_keyMap[key] == KEY_INACTIVE && m_previousKeyMap[key] == KEY_DOWN)
	{
		return KEY_UP;
	}
	else
	{
		return KEY_INACTIVE;
	}
}
