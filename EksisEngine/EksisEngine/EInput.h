#pragma once

#include "EKeyboard.h"
#include "EMouse.h"

class EInput
{
private:
	EKeyboard m_keyboard;
	EMouse m_mouse;

	// Find a way to store keybinds (and a way to have different keybinds
	// based on the context).
	int m_context;
public:
	EInput();

	void Shutdown();

	EKeyboard* GetKeyboard();
	EMouse* GetMouse();

	void PollInput();
	int GetState(EKeyCode);
};
